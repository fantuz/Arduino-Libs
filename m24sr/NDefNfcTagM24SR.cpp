/**
  ******************************************************************************
  * @file       NdefNfcTagSTM24SR.cpp
  * @author  	ST Central Labs
  * @version V1.1.0
  * @date    30 Set 2016
  * @brief      Wrapper class of the NDefLib library to write/read NDEF messages
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include <cmath>

#include "NDefNfcTagM24SR.h"


/* wait 1sec, driver is configured to let 200ms for command to complete */
/* which is enough for all commands except GetSession if RF session is already opened */
/* Smartphone generally releases the session within the second, anyway the user can modify this value */
#define OPENSESSION_NTRIALS 5

#define CC_FILE_LENGTH_BYTE 15
////////////////////////////START  OpenSessionCallBack/////////////////////////
NDefNfcTagM24SR::OpenSessionCallBack::
	OpenSessionCallBack(NDefNfcTagM24SR& sender):
		mSender(sender),mNTrials(OPENSESSION_NTRIALS){}

void NDefNfcTagM24SR::OpenSessionCallBack::onSessionOpen(M24SR *nfc,
		M24SR::StatusTypeDef status){
	if(status==M24SR::M24SR_SUCCESS){
		nfc->SelectApplication();
	}else{
		mSender.mCallBack->onSessionOpen(&mSender,false);
	}
}

void NDefNfcTagM24SR::OpenSessionCallBack::onSelectedApplication(M24SR *nfc,
		M24SR::StatusTypeDef status){
	if(status==M24SR::M24SR_SUCCESS){
		nfc->SelectCCfile();
	}else{
		if(mNTrials==0)
			mSender.mCallBack->onSessionOpen(&mSender,false);
		else{
			mNTrials--;
			nfc->SelectApplication();
		}//if-else
	}//if-else
}

void NDefNfcTagM24SR::OpenSessionCallBack::onSelectedCCFile(M24SR *nfc,
		M24SR::StatusTypeDef status){
	if(status==M24SR::M24SR_SUCCESS){
		nfc->ReadBinary(0x0000, CC_FILE_LENGTH_BYTE, CCFile);
	}else{
		mSender.mCallBack->onSessionOpen(&mSender,false);
	}
}

void NDefNfcTagM24SR::OpenSessionCallBack::onReadByte(M24SR *nfc,
		M24SR::StatusTypeDef status,uint16_t offset,uint8_t *readByte, uint16_t nReadByte){
	(void)offset;
	if(status!=M24SR::M24SR_SUCCESS || nReadByte!=CC_FILE_LENGTH_BYTE){
		return mSender.mCallBack->onSessionOpen(&mSender,false);
	}//else
	uint16_t NDefFileId = (uint16_t) ((readByte[0x09] << 8) | readByte[0x0A]);
	mSender.mMaxReadBytes = (uint16_t) ((readByte[0x03] << 8) | readByte[0x04]);
	mSender.mMaxWriteBytes = (uint16_t) ((readByte[0x05] << 8) | readByte[0x06]);
	nfc->SelectNDEFfile(NDefFileId);
}

void NDefNfcTagM24SR::OpenSessionCallBack::onSelectedNDEFFile(M24SR *nfc,
		M24SR::StatusTypeDef status){
	(void)nfc;

	mSender.mIsSessionOpen = status==M24SR::M24SR_SUCCESS;
	mSender.mCallBack->onSessionOpen(&mSender,mSender.mIsSessionOpen);
}
////////////////////////////END  OpenSessionCallBack/////////////////////////

bool NDefNfcTagM24SR::openSession(bool force) {

	if (isSessionOpen()){
		mCallBack->onSessionOpen(this,true);
		return true;
	}

	mDevice.SetCallback(&mOpenSessionCallback);
	if(force)
		return mDevice.ForceGetSession() == M24SR::M24SR_SUCCESS;
	else
		return mDevice.GetSession() == M24SR::M24SR_SUCCESS;


}

bool NDefNfcTagM24SR::closeSession() {
	mDevice.SetCallback(&mCloseSessionCallback);
	return mDevice.Deselect() == M24SR::M24SR_SUCCESS;
}

void NDefNfcTagM24SR::WriteByteCallback::onUpdatedBinary(M24SR *nfc,
		M24SR::StatusTypeDef status,uint16_t startOffset, uint8_t *writeByte,uint16_t nWriteByte){

	if(status!=M24SR::M24SR_SUCCESS){ // error -> finish to write
		mCallback(mCallbackParam,false,mByteToWrite,mNByteToWrite);
		return;
	}//else

	mByteWrote+=nWriteByte;
	if(mByteWrote==mNByteToWrite){ //write all -> finish
		mCallback(mCallbackParam,true,mByteToWrite,mNByteToWrite);
	}else{ //else write another slice
		uint16_t tempLenght = std::min(mSender.mMaxWriteBytes,
				(uint16_t)(mNByteToWrite-mByteWrote));
		nfc->UpdateBinary(startOffset+nWriteByte,tempLenght,writeByte+nWriteByte);
	}//if-else
}

bool NDefNfcTagM24SR::writeByte(const uint8_t *buffer, uint16_t length,uint16_t offset,
		byteOperationCallback_t callback,CallbackStatus_t *callbackStatus){
	if(!isSessionOpen())
		callback(callbackStatus,false,buffer,length);
	//else
	mWriteByteCallback.setTask(buffer,length,callback,callbackStatus);
	mDevice.SetCallback(&mWriteByteCallback);

	if (length > mMaxWriteBytes) {
		return mDevice.UpdateBinary(offset, mMaxWriteBytes,(uint8_t*) buffer) == M24SR::M24SR_SUCCESS;
	}else{
		return mDevice.UpdateBinary(offset,length,(uint8_t*)buffer) == M24SR::M24SR_SUCCESS;
	}//if-else

}

void NDefNfcTagM24SR::ReadByteCallback::onReadByte(M24SR *nfc,
		M24SR::StatusTypeDef status,uint16_t startOffset, uint8_t *readBffer,uint16_t nReadByte){

	if(status!=M24SR::M24SR_SUCCESS){ // error -> finish to write
		mCallback(mCallbackParam,false,mBuffer,mNByteToRead);
		return;
	}//else

	mByteRead += nReadByte;
	if(mByteRead==mNByteToRead){ //read all -> finish
		mCallback(mCallbackParam,true,mBuffer,mNByteToRead);
	}else{ //else write another slice
		uint16_t tempLenght = std::min(mSender.mMaxReadBytes,
				(uint16_t)(mNByteToRead-mByteRead));
		nfc->ReadBinary(startOffset+nReadByte,tempLenght,readBffer+nReadByte);
	}//if-else

}

bool NDefNfcTagM24SR::readByte(const uint16_t byteOffset, const uint16_t length,
		uint8_t *buffer, byteOperationCallback_t callback,CallbackStatus_t *callbackStatus){
	if(!isSessionOpen()){
		return callback(callbackStatus,false,buffer,length);
	}
	//else
	mReadByteCallback.setTask(buffer,length,callback,callbackStatus);
	mDevice.SetCallback(&mReadByteCallback);

	if (length > mMaxReadBytes) {
		return mDevice.ReadBinary(byteOffset, mMaxReadBytes,buffer)== M24SR::M24SR_SUCCESS;;
	}else{
		return mDevice.ReadBinary(byteOffset,length,buffer)== M24SR::M24SR_SUCCESS;;
	}//if-else

}

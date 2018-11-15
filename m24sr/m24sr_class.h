/**
 ******************************************************************************
 * @file    m24sr_class.h
 * @author  ST Central Labs
 * @version V1.1.0
 * @date    30 Set 2016
 * @brief   This file provides a set of functions to interface with the M24SR
 *          device.
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

/* Revision ------------------------------------------------------------------*/
/*
 Based on:         X-CUBE-MEMS1/trunk/Drivers/BSP/Components/m24sr/m24sr.h
 Revision:         M24SR Driver V1.0.0
 */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __M24SR_CLASS_H
#define __M24SR_CLASS_H

/* Includes ------------------------------------------------------------------*/

#include "mbed.h"
#include "I2C.h"

#include "m24sr.h"
#include "Nfc.h"

#include "NDefLib/NDefNfcTag.h"
class NDefNfcTagM24SR;

/* Classes -------------------------------------------------------------------*/

/**
* Class representing a M24SR component.
* This component has two operation modes, sync or async.
* In sync mode each function call returns only after the command has completed.
* In async mode each function call returns immediately and the answer will be notified
* through a callback.
* The default behavior is sync mode.
* To enable the async mode ManageI2CGPO(I2C_ANSWER_READY) function must be called.
* When the component notifies an interrupt user must call  {@link ManageEvent} function.
* Note that passing a parameter other than I2C_ANSWER_READY to ManageI2CGPO initialize the component in sync mode.
 */
class M24SR: public Nfc {

public:

	typedef enum {
		M24SR_SUCCESS=NFC_SUCCESS,
		M24SR_ERROR=0x6F00,
		M24SR_FILE_OVERFLOW_LE = 0x6280,
		M24SR_EOF = 0x6282,
		M24SR_PASSWORD_REQUIRED = 0x6300,
		M24SR_PASSWORD_INCORRECT = 0x63C0,
		M24SR_PASSWORD_INCORRECT1RETRY = 0x63C1,
		M24SR_PASSWORD_INCORRECT2RETRY = 0x63C2,
		M24SR_WRONG_LENGHT = 0x6700,
		M24SR_UNSUCESSFUL_UPDATING = 0x6581,
		M24SR_INCOPATIBLE_COMMAND= 0x6981,
		M24SR_SECURITY_UNSATISFIED = 0x6982,
		M24SR_REFERENCE_DATA_NOT_USABLE = 0x6984,

		M24SR_INCORRECT_PARAMETER = 0x6a80,
		M24SR_FILE_NOT_FOUND=0x6a82,
		M24SR_FILE_OVERFLOW_LC = 0x6A84, //TODO difference with Le??

		M24SR_INCORRECT_P1_OR_P2 = 0x6A86, //TODO better name?
		M24SR_RF_SESSION_KILLED=0x6500,
		M24SR_INS_NOT_SUPPORTED=0x6D00,
		M24SR_CLASS_NOT_SUPPORTED=0x6E00,

		//IOError
		M24SR_IO_ERROR_I2CTIMEOUT=0x0011,
		M24SR_IO_ERROR_CRC=0x0012,
		M24SR_IO_ERROR_NACK=0x0013,
		M24SR_IO_ERROR_PARAMETER=0x0014,
		M24SR_IO_ERROR_NBATEMPT=0x0015,
		M24SR_IO_NOACKNOWLEDGE=0x0016
	} StatusTypeDef;

	/**
	 * @brief  GPO state structure
	 */
	typedef enum {
		HIGH_IMPEDANCE = 0,
		SESSION_OPENED =1,
		WIP=2,
		I2C_ANSWER_READY=3,
		INTERRUPT=4,
		STATE_CONTROL=5
	} NFC_GPO_MGMT;

	/**
	 * Possible password to set.
	 */
	typedef enum{
		ReadPwd,   //!< Password to use before reading the tag
		WritePwd,  //!< Password to use before writing the tag
		I2CPwd,    //!< Root password, used only through nfc
	}PasswordType_t;

	/**
	 * Default password used to change the write/read permission
	 */
	static const uint8_t DEFAULT_PASSWORD[16];

	/**
	 * Default gpo status -> the gpo will remain high
	 */
	static const NFC_GPO_MGMT DEFAULT_GPO_STATUS=HIGH_IMPEDANCE;


	/**
	 * Function that will be called when an interrupt is fired,
	 * this function must be set if you want use the component in async mode.
	 */
	typedef void(*gpoEventCallback)(void);

	/**
	 * Object that contains all the callbacks fired by this class, each command has its own callback.
	 * The callback default implementation is an empty function.
	 */
	class Callbacks{
		public:

			/** called when GetSession or ForceGetSession completes
			 * @see M24SR#GetSession
			 * @see M24SR#ForceGetSession */
			virtual void onSessionOpen(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when Deselect completes
			 * @see M24SR#Deselect */
			virtual void onDeselect(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when SelectedApplication completes
			 * @see M24SR#SelectedApplication */
			virtual void onSelectedApplication(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when SelectedCCFile completes
			 * @see M24SR#SelectedCCFile */
			virtual void onSelectedCCFile(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when SelectedNDEFFile completes
			 * @see M24SR#SelectedNDEFFile */
			virtual void onSelectedNDEFFile(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when SelectedSystemFile completes
			 * @see M24SR#SelectedSystemFile */
			virtual void onSelectedSystemFile(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when ReadBinary or STReadBinary completes
			 * @see M24SR#ReadBinary
			 * @see M24SR#STReadBinary */
			virtual void onReadByte(M24SR *nfc,StatusTypeDef status,
					uint16_t offset,uint8_t *readByte, uint16_t nReadByte){
				(void)nfc; (void)status;(void)offset; (void)readByte; (void)nReadByte;
			}

			/** called when UpdatedBinary completes
			 * @see M24SR#UpdatedBinary */
			virtual void onUpdatedBinary(M24SR *nfc,StatusTypeDef status,uint16_t offset,
					uint8_t *writeByte,uint16_t nWriteByte){
				(void)nfc; (void)status; (void)writeByte; (void)nWriteByte; (void)offset;
			}

			/** called when Verify completes
			 * @see M24SR#Verify */
			virtual void onVerified(M24SR *nfc,StatusTypeDef status,PasswordType_t uPwdId,
					const uint8_t *pwd){
				(void)nfc; (void)status;(void)uPwdId;(void)pwd;
			}

			/** called when ManageI2CGPO completes
			 * @see M24SR#ManageI2CGPO */
			virtual void onManageI2CGPO(M24SR *nfc,StatusTypeDef status,NFC_GPO_MGMT newStatus){
				(void)nfc; (void)status;(void)newStatus;
			}

			/** called when ManageRFGPO completes
			 * @see M24SR#ManageRFGPO */
			virtual void onManageRFGPO(M24SR *nfc,StatusTypeDef status,NFC_GPO_MGMT newStatus){
				(void)nfc; (void)status;(void)newStatus;
			}

			/** called when ChangeReferenceData completes
			 * @see M24SR#ChangeReferenceData */
			virtual void onChangeReferenceData(M24SR *nfc ,StatusTypeDef status,PasswordType_t type,
					uint8_t *data){
				(void)nfc; (void)status;(void)type;(void)data;
			}

			/** called when EnableVerificationRequirement completes
			 * @see M24SR#EnableVerificationRequirement */
			virtual void onEnableVerificationRequirement(M24SR *nfc ,StatusTypeDef status,PasswordType_t type){
				(void)nfc; (void)status;(void)type;
			}

			/** called when DisableVerificationRequirement completes
			 * @see M24SR#DisableVerificationRequirement */
			virtual void onDisableVerificationRequirement(M24SR *nfc , StatusTypeDef status,PasswordType_t type){
				(void)nfc; (void)status;(void)type;
			}

			/** called when EnablePermanentState completes
			 * @see M24SR#EnablePermanentState */
			virtual void onEnablePermanentState(M24SR *nfc, StatusTypeDef status, PasswordType_t type){
				(void)nfc; (void)status;(void)type;
			}

			/** called when DisablePermanentState completes
			 * @see M24SR#DisablePermanentState */
			virtual void onDisablePermanentState(M24SR *nfc, StatusTypeDef status, PasswordType_t type){
				(void)nfc; (void)status;(void)type;
			}

			/** called when ReadId completes
			 * @see M24SR#ReadId */
			virtual void onReadId(M24SR *nfc, StatusTypeDef status, uint8_t *id){
						(void)nfc; (void)status;(void)id;
			}

			/** called when EnableReadPassword completes
			 * @see M24SR#EnableReadPassword */
			virtual void onEnableReadPassword(M24SR *nfc, StatusTypeDef status,const uint8_t *newPwd){
				(void)nfc; (void)status;(void)newPwd;
			}

			/** called when EnableWritePassword completes
			 * @see M24SR#EnableWritePassword */
			virtual void onEnableWritePassword(M24SR *nfc, StatusTypeDef status,const uint8_t *newPwd){
				(void)nfc; (void)status;(void)newPwd;
			}

			/** called when DisableReadPassword completes
			 * @see M24SR#DisableReadPassword */
			virtual void onDisableReadPassword(M24SR *nfc, StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when DisableWritePassword completes
			 * @see M24SR#DisableWritePassword */
			virtual void onDisableWritePassword(M24SR *nfc, StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when DisableAllPassword completes
			 * @see M24SR#DisableAllPassword */
			virtual void onDisableAllPassword(M24SR *nfc, StatusTypeDef status){
				(void)nfc; (void)status;
			}


			/** called when EnableReadOnly completes
			 * @see M24SR#EnableReadOnly */
			virtual void onEnableReadOnly(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when EnableWriteOnly completes
			 * @see M24SR#EnableWriteOnly */
			virtual void onEnableWriteOnly(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}


			/** called when DisableReadOnly completes
			 * @see M24SR#DisableReadOnly */
			virtual void onDisableReadOnly(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			/** called when DisableWriteOnly completes
			 * @see M24SR#DisableWriteOnly */
			virtual void onDisableWriteOnly(M24SR *nfc,StatusTypeDef status){
				(void)nfc; (void)status;
			}

			virtual ~Callbacks(){};
		};

	/*** Constructor and Destructor Methods ***/

	/**
	 * @brief Constructor.
	 * @param address I2C address of the component.
	 * @param I2C     I2C device to be used for communication.
	 * @param eventCallback Function that will be called when the gpo pin status changes.
	 * @param GPOPinName Pin used as GPIO.
	 * @param RFDISPinName Pin used to disable the RF function.
	 */
	M24SR(const uint8_t address, I2C &I2C,gpoEventCallback eventCallback, const PinName& GPOPinName,
			const PinName& RFDISPinName);

	/**
	 * @brief Destructor.
	 */
	virtual ~M24SR(void);

	/*** Public Component Related Methods ***/
	
	/**
	 * @brief  This function initializes the M24SR device.
	 * @param ptr Configure parameters, not used.
     * @return M24SR_SUCCESS if no errors
	 */
	virtual int Init(void *ptr) {
		return (StatusTypeDef) M24SR_Init((M24SR_InitTypeDef*)ptr);
	}

	virtual int ReadID(uint8_t *id) {
		return (StatusTypeDef) M24SR_ReadID((uint8_t *) id);
	}

	/** lock the tag channel */
	virtual StatusTypeDef GetSession(void) {
		return (StatusTypeDef) M24SR_GetSession();
	}

	/**
	 * Force to open an I2C connection , abort the RF connection.
	 * @return M24SR_SUCCESS if the session is acquired
	 */
	StatusTypeDef ForceGetSession(void) {
		return (StatusTypeDef) M24SR_ForceSession();
	}

	virtual StatusTypeDef Deselect(void) {
		return (StatusTypeDef) M24SR_Deselect();
	}

	////////// tag4 command ////////////////////
	
	/**
	 * Select the application file.
	 * @return M24SR_SUCCESS if the application is selected
	 */
	StatusTypeDef SelectApplication(void) {
		return M24SR_SendSelectApplication();
	}

	/**
	 * Select the CC file.
	 * @return M24SR_SUCCESS if the CC file is selected.
	 */
	StatusTypeDef SelectCCfile(void) {
		return M24SR_SendSelectCCfile();
	}

	/**
	 * Select the NDEF file.
	 * @param NDEFfileId File id to open.
	 * @return M24SR_SUCCESS if the file is selected
	 */
	StatusTypeDef SelectNDEFfile(uint16_t NDEFfileId) {
		return M24SR_SendSelectNDEFfile(NDEFfileId);
	}

	/**
	 * Select the system file.
	 * @return M24SR_SUCCESS if the system file is selected
	 */
	StatusTypeDef SelectSystemfile(void) {
		return M24SR_SendSelectSystemfile();
	}

	virtual int ReadBinary(uint16_t Offset, uint8_t NbByteToRead,
			uint8_t *pBufferRead) {
		return (StatusTypeDef) M24SR_SendReadBinary((uint16_t) Offset,
				(uint8_t) NbByteToRead, (uint8_t *) pBufferRead);
	}

	virtual int UpdateBinary(uint16_t Offset,
			uint8_t NbByteToWrite,uint8_t *pDataToWrite) {
		return (StatusTypeDef) M24SR_SendUpdateBinary((uint16_t) Offset,
				(uint8_t) NbByteToWrite, (uint8_t *) pDataToWrite);
	}

	/////////////////// iso 7816-4 commands //////////////////////////
	
	virtual StatusTypeDef Verify(PasswordType_t pwdId, uint8_t NbPwdByte,
			const uint8_t *pPwd) {
		return (StatusTypeDef) M24SR_SendVerify(passwordTypeToConst(pwdId),
				(uint8_t) NbPwdByte, pPwd);
	}

	virtual StatusTypeDef ChangeReferenceData(PasswordType_t pwdId,
			const uint8_t *pPwd) {
		return (StatusTypeDef) M24SR_SendChangeReferenceData(passwordTypeToConst(pwdId),
				(uint8_t *) pPwd);
	}

	virtual StatusTypeDef EnableVerificationRequirement(
			PasswordType_t uReadOrWrite) {
		return (StatusTypeDef) M24SR_SendEnableVerificationRequirement(
				passwordTypeToConst(uReadOrWrite));
	}

	virtual StatusTypeDef DisableVerificationRequirement(
			PasswordType_t uReadOrWrite) {
		return (StatusTypeDef) M24SR_SendDisableVerificationRequirement(
				passwordTypeToConst(uReadOrWrite));
	}

    ////////////////////// ST proprietary //////////////////////////////////

	/**
	 * Same as {@link NFC#ReadBinary}, however permitting to read more bytes than available.
	 * @param Offset read offset.
	 * @param NbByteToRead Number of bytes to read.
	 * @param[out] pBufferRead Buffer to store the read data into.
	 * @return M24SR_SUCCESS if no errors
	 */
	StatusTypeDef STReadBinary(uint16_t Offset,
			uint8_t NbByteToRead, uint8_t *pBufferRead) {
		return (StatusTypeDef) M24SR_SendSTReadBinary((uint16_t) Offset,
				(uint8_t) NbByteToRead, (uint8_t *) pBufferRead);
	}

	virtual StatusTypeDef EnablePermanentState(PasswordType_t uReadOrWrite) {
		return (StatusTypeDef) M24SR_SendEnablePermanentState(
				passwordTypeToConst(uReadOrWrite));
	}

	virtual StatusTypeDef DisablePermanentState(PasswordType_t uReadOrWrite) {
		return (StatusTypeDef) M24SR_SendDisablePermanentState(
				passwordTypeToConst(uReadOrWrite));
	}

	///////////////////// chip configuration /////////////////////////////////
	/**
	 * Set the gpo output pin.
	 * @param uSetOrReset New pin status.
 	 * @return M24SR_SUCCESS if no errors
	 */
	StatusTypeDef StateControl(uint8_t uSetOrReset) {
		return (StatusTypeDef) M24SR_StateControl((uint8_t) uSetOrReset);
	}

	/**
	 * @brief  This function configures GPO for I2C session.
	 * @param  GPO_I2Cconfig GPO configuration to set.
 	 * @return M24SR_SUCCESS if no errors
 	 * @par if the configuration is I2C_ANSWER_READY, the component will start to work
 	 * in async mode.
	 */
	StatusTypeDef ManageI2CGPO(NFC_GPO_MGMT GPO_I2Cconfig) {
		return (StatusTypeDef) M24SR_ManageI2CGPO(GPO_I2Cconfig);
	}


	/**
 	* @brief  This function configures GPO for RF session.
 	* @param  GPO_RFconfig GPO configuration to set.
  	* @return M24SR_SUCCESS if no errors
 	*/
	StatusTypeDef ManageRFGPO(uint8_t GPO_RFconfig) {
		return (StatusTypeDef) M24SR_ManageRFGPO(
				(NFC_GPO_MGMT) GPO_RFconfig);
	}


	/**
	 * @brief  This function enables or disables the RF communication.
	 * @param  OnOffChoice GPO configuration to set.
  	 * @return M24SR_SUCCESS if no errors
	 */

	StatusTypeDef RFConfig(uint8_t OnOffChoice) {
		return (StatusTypeDef) M24SR_RFConfig((uint8_t) OnOffChoice);
	}


	/**
	 * Generates a negative pulse on the GPO pin.
	 * Pulse starts immediately after the command is issued and ends at the end of the RF response.
  	 * @return M24SR_SUCCESS if no errors
	 */
	StatusTypeDef SendInterrupt(void) {
		return (StatusTypeDef) M24SR_SendInterrupt();
	}


	/**
	 * Function to call when the component fire an interrupt.
	 * @return last operation status
	 */
	StatusTypeDef ManageEvent();

	/**
	 * Change the function to call when a command ends.
	 * @param commandCallback Object containing the callback, if NULL it will use empty callback
	 */
	void SetCallback(Callbacks *commandCallback){
		if(commandCallback!=NULL)
			mCallback = commandCallback;
		else
			mCallback = &defaultCallback;
	}


	/////////////////// hight level/utility function /////////////////////


	/**
	 * Enable the request of a password before reading the tag.
	 * @param  pCurrentWritePassword Current password
	 * @param  pNewPassword Password to request before reading the tag.
	 * @return return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef EnableReadPassword(const uint8_t* pCurrentWritePassword,
				const uint8_t* pNewPassword) {

		//enable the callback for change the gpo
		mComponentCallback = &mChangePasswordRequestStatusCallback;
		mChangePasswordRequestStatusCallback.setTask(ReadPwd,pNewPassword);

		return Verify(M24SR::WritePwd, 0x10, pCurrentWritePassword);
	}

	/**
	 * Disable the request of a password before reading the tag.
	 * @param  pCurrentWritePassword Current password
	 * @return return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef DisableReadPassword(const uint8_t* pCurrentWritePassword) {
		mComponentCallback = &mChangePasswordRequestStatusCallback;
		mChangePasswordRequestStatusCallback.setTask(ReadPwd,NULL);

		return Verify(M24SR::WritePwd, 0x10, pCurrentWritePassword);
	}

	/**
	 * Enable the request of a password before writing to the tag.
	 * @param  pCurrentWritePassword Current password
	 * @param  pNewPassword Password to request before reading the tag.
	 * @return return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef EnableWritePassword(const uint8_t* pCurrentWritePassword,
				uint8_t* pNewPassword) {
		//enable the callback for change the gpo
		mComponentCallback = &mChangePasswordRequestStatusCallback;
		mChangePasswordRequestStatusCallback.setTask(WritePwd,pNewPassword);

		return Verify(M24SR::WritePwd, 0x10, pCurrentWritePassword);
	}

	/**
	 * Disable the request of a password before writing the tag.
	 * @param  pCurrentWritePassword Current password.
	 * @return return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef DisableWritePassword(const uint8_t* pCurrentWritePassword) {
		mComponentCallback = &mChangePasswordRequestStatusCallback;
		mChangePasswordRequestStatusCallback.setTask(WritePwd,NULL);

		return Verify(M24SR::WritePwd, 0x10, pCurrentWritePassword);
	}

	/**
	 * @brief   This function disables both read and write passwords.
	 * @param	pSuperUserPassword I2C super user password.
	 * @return  return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef DisableAllPassword(const uint8_t* pSuperUserPassword){
		mComponentCallback = &mRemoveAllPasswordCallback;
		return Verify(M24SR::I2CPwd, 0x10, pSuperUserPassword);
	}

	/**
	 * @brief   This function enables read only mode.
	 * @param	pCurrentWritePassword Write password is needed to enable read only mode.
	 * @return  return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef EnableReadOnly(const uint8_t* pCurrentWritePassword){

		mComponentCallback = &mChangeAccessStateCallback;
		//disable write = read only
		mChangeAccessStateCallback.changeAccessState(ChangeAccessStateCallback::WRITE,false);

		return Verify(M24SR::WritePwd, 0x10, pCurrentWritePassword);
	}

	/**
	 * @brief   This function disables read only mode.
	 * @param	pCurrentWritePassword Write password is needed to disable read only mode.
	 * @return  return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef DisableReadOnly(const uint8_t* pCurrentWritePassword) {
		mComponentCallback = &mChangeAccessStateCallback;
		mChangeAccessStateCallback.changeAccessState(ChangeAccessStateCallback::WRITE,true);
		return Verify(M24SR::I2CPwd, 0x10,pCurrentWritePassword);
	}


	/**
	 * @brief   This function enables write only mode.
	 * @param	pCurrentWritePassword Write password is needed to enable write only mode.
	 * @return  return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef EnableWriteOnly(const uint8_t* pCurrentWritePassword) {

		mComponentCallback = &mChangeAccessStateCallback;
		//disable read = enable write only
		mChangeAccessStateCallback.changeAccessState(ChangeAccessStateCallback::READ,false);

		return Verify(M24SR::WritePwd, 0x10, pCurrentWritePassword);

	}

	/**
	 * @brief   This function disables write only mode.
	 * @param	pCurrentWritePassword Write password is needed to disable write only mode.
	 * @return  return M24SR_SUCCESS if no errors
	 * @par The password must have a length of 16 chars.
	 */
	StatusTypeDef DisableWriteOnly(const uint8_t* pCurrentWritePassword) {
		mComponentCallback = &mChangeAccessStateCallback;
		mChangeAccessStateCallback.changeAccessState(ChangeAccessStateCallback::READ,true);
		return Verify(M24SR::I2CPwd, 0x10, pCurrentWritePassword);
	}


	/**
	 * Get an implementation of NDefNfcTag to use the library NDefLib.
	 * @return an object of type NdefNfcTag 
	 */
	NDefLib::NDefNfcTag& getNDefTag();


protected:

	/*** Protected Component Related Methods ***/

	StatusTypeDef M24SR_Init(M24SR_InitTypeDef *);
	StatusTypeDef M24SR_ReadID(uint8_t *nfc_id);
	StatusTypeDef M24SR_GetSession(void);
	StatusTypeDef M24SR_ForceSession(void);



	StatusTypeDef M24SR_Deselect(void);
	StatusTypeDef M24SR_ReceiveDeselect(void);

	StatusTypeDef M24SR_SendSelectApplication(void);
	StatusTypeDef M24SR_ReceiveSelectApplication(void);

	StatusTypeDef M24SR_SendSelectCCfile(void);
	StatusTypeDef M24SR_ReceiveSelectCCfile(void);

	StatusTypeDef M24SR_SendSelectNDEFfile(uint16_t NDEFfileId);
	StatusTypeDef M24SR_ReceiveSelectNDEFfile();

	StatusTypeDef M24SR_SendSelectSystemfile(void);
	StatusTypeDef M24SR_ReceiveSelectSystemfile(void);

	StatusTypeDef M24SR_SendReadBinary(uint16_t Offset, uint8_t NbByteToRead,
			uint8_t *pBufferRead);
	StatusTypeDef M24SR_SendSTReadBinary(uint16_t Offset, uint8_t NbByteToRead,
				uint8_t *pBufferRead);
	StatusTypeDef M24SR_ReceiveReadBinary(void);

	StatusTypeDef M24SR_SendUpdateBinary(uint16_t Offset, uint8_t NbByteToWrite,
			uint8_t *pDataToWrite);
	StatusTypeDef M24SR_ReceiveUpdateBinary();

	StatusTypeDef M24SR_SendVerify(uint16_t uPwdId, uint8_t NbPwdByte,
			const uint8_t *pPwd);
	StatusTypeDef M24SR_ReceiveVerify();

	StatusTypeDef M24SR_SendChangeReferenceData(uint16_t uPwdId, uint8_t *pPwd);
	StatusTypeDef M24SR_ReceiveChangeReferenceData();

	StatusTypeDef M24SR_SendEnableVerificationRequirement(
			uint16_t uReadOrWrite);
	StatusTypeDef M24SR_ReceiveEnableVerificationRequirement();

	StatusTypeDef M24SR_SendDisableVerificationRequirement(
			uint16_t uReadOrWrite);
	StatusTypeDef M24SR_ReceiveDisableVerificationRequirement();

	StatusTypeDef M24SR_SendEnablePermanentState(uint16_t uReadOrWrite);
	StatusTypeDef M24SR_ReceiveEnablePermanentState();

	StatusTypeDef M24SR_SendDisablePermanentState(uint16_t uReadOrWrite);
	StatusTypeDef M24SR_ReceiveDisablePermanentState();

	StatusTypeDef M24SR_SendInterrupt(void);
	StatusTypeDef M24SR_StateControl(uint8_t uSetOrReset);

	StatusTypeDef M24SR_ManageI2CGPO(NFC_GPO_MGMT GPO_I2Cconfig);
	StatusTypeDef M24SR_ManageRFGPO(NFC_GPO_MGMT GPO_RFconfig);

	StatusTypeDef M24SR_RFConfig(uint8_t OnOffChoice);
	StatusTypeDef M24SR_SendFWTExtension(uint8_t FWTbyte);

	
	/**
	 * Send a command to the component.
	 * @param NbByte Length of the command.
	 * @param pBuffer Buffer containing the command.
	 * @return M24SR_SUCCESS if no errors
	 */
	StatusTypeDef M24SR_IO_SendI2Ccommand(uint8_t NbByte, uint8_t *pBuffer);
	
	/**
	 * Read a command response.
	 * @param NbByte Number of bytes to read.
	 * @param pBuffer Buffer to store the response into.
	 * @return M24SR_SUCCESS if no errors
	 */
	StatusTypeDef M24SR_IO_ReceiveI2Cresponse(uint8_t NbByte,
			uint8_t *pBuffer);

	/**
	 * Do an active polling on the I2C bus until the answer is ready.
	 * @return M24SR_SUCCESS if no errors
	 */
	StatusTypeDef M24SR_IO_PollI2C(void);

	/**
	 * Read the gpo pin.
	 * @param[out] pPinState Variable to store the pin state into.
	 */
	void M24SR_IO_GPO_ReadPin(uint8_t *pPinState) {
		*pPinState= GPOPin.read();
	}

	/**
	 * Write the gpo pin.
	 * @param pPinState Pin state to write.
	 */
	void M24SR_IO_RFDIS_WritePin(uint8_t PinState) {
		if (PinState == 0)
			RFDisablePin = 0;
		else
			RFDisablePin = 1;
	}

	/*** Component's Instance Variables ***/

	/* Identity */
	uint8_t who_am_i;

	/* Type */
	uint8_t type;

	/* I2C address */
	uint8_t address;

	/* IO Device. */
	I2C &dev_I2C;

	/* GPIO */
	DigitalIn GPOPin;

	/**
	 * Pin used to disable the rf chip functionality.
	 */
	DigitalOut RFDisablePin;

	/**
	 * Buffer used to build the command to send to the chip.
	 */
	uint8_t uM24SRbuffer[0xFF];//max command length is 255

	/**
	 * ???
	 */
	uint8_t uDIDbyte;


	/**
	 * Command that the component can accept
	 */
	typedef enum{
		NONE,                            //!< NONE
		DESELECT,                        //!< DESELECT
		SELECT_APPLICATION,              //!< SELECT_APPLICATION
		SELECT_CC_FILE,                  //!< SELECT_CC_FILE
		SELECT_NDEF_FILE,                //!< SELECT_NDEF_FILE
		SELECT_SYSTEM_FILE,              //!< SELECT_SYSTEM_FILE
		READ,                            //!< READ
		UPDATE,                          //!< UPDATE
		VERIFY,                          //!< VERIFY
		MANAGE_I2C_GPO,                  //!< MANAGE_I2C_GPO
		MANAGE_RF_GPO,                   //!< MANAGE_RF_GPO
		CHANGE_REFERENCE_DATA,           //!< CHANGE_REFERENCE_DATA
		ENABLE_VERIFICATION_REQUIREMENT, //!< ENABLE_VERIFICATION_REQUIREMENT
		DISABLE_VERIFICATION_REQUIREMENT,//!< DISABLE_VERIFICATION_REQUIREMENT
		ENABLE_PERMANET_STATE,           //!< ENABLE_PERMANET_STATE
		DISABLE_PERMANET_STATE,          //!< DISABLE_PERMANET_STATE
	}M24SR_command_t;

	/**
 	 * User parameter used to invoke a command,
 	 * it is used to provide the data back with the response
	 */
	typedef struct{
		uint8_t *data; //!< data
		uint16_t length; //!< number of bytes in the data array
		uint16_t offset; //!< offset parameter used in the read/write command
	}M24SR_command_data_t;

	/**
	 * Communication mode used by this device
	 */
	typedef enum{
		SYNC,//!< SYNC wait the command response before returning
		ASYNC//!< ASYNC use a callback to notify the end of a command
	}M24SR_communication_t;

	/**
	 * Type of communication being used
	 */
	M24SR_communication_t mCommunicationType;

	/**
	 * Last pending command
	 */
	M24SR_command_t mLastCommandSend;

	/**
	 * Parameter used to invoke the last command
	 */
	M24SR_command_data_t mLastCommandData;

	/**
	 * Interrupt object fired when the gpo status changes
	 */
	InterruptIn mGpoEventInterrupt;

	/** object containing the callbacks to use*/
	Callbacks *mCallback;

	/**
	 * Object with private callbacks used to hide high level commands each
	 * calling multiple low level commands. This callbacks object has
	 * higher priority comparing to the user callbacks.
	 */
	Callbacks *mComponentCallback;

	/**
	 * Object implementing the interface to use the NDefLib.
	 */
	NDefNfcTagM24SR *mNDefTagUtil;

	/**
	 * get the callback object to use
	 * @return callback object to use
	 */
	Callbacks * getCallback(){
		if(mComponentCallback!=NULL)
			return mComponentCallback;
		return mCallback;
	}//getCallback

private:
	/** object containing empty callback to use in the default case*/
	Callbacks defaultCallback;


	/**
	 * This class permits to enable/disable the password request to read/write into the tag
	 * This class is equivalent to calling the methods:
	 * To enable the request:
	 * <ul>
	 *   <li> Verify </li>
	 *   <li> ChangeReferenceData </li>
	 *   <li> EnablePermanentState </li>
	 * </ul>
	 * To disable the request:
	 * <ul>
	 *   <li> Verify </li>
	 *   <li> DisableVerificationRequirement </li>
	 * </ul>
	 */
	class ChangePasswordRequestStatusCallback : public Callbacks{

		public:

			/**
			 * Build the chain of callbacks.
			 */
			ChangePasswordRequestStatusCallback():
				mNewPwd(NULL),mType(I2CPwd),mEnable(false){}

			/**
			 * Set the password to enable/disable.
			 * @param type Type of password to enable/disable.
			 * @param newPwd Array of 16bytes with the new password, if null the request will be disabled.
			 */
			void setTask(PasswordType_t type, const uint8_t *newPwd){
				mNewPwd=newPwd;
				mType=type;
				mEnable=newPwd!=NULL;
			}//setTask

			virtual void onVerified(M24SR *nfc, StatusTypeDef status,PasswordType_t ,
					const uint8_t *){
				if(status!=M24SR_SUCCESS)
					return onFinishCommand(nfc,status);
				if(mEnable)
					nfc->ChangeReferenceData(mType,mNewPwd);
				else
					nfc->DisableVerificationRequirement(mType);
			}

			virtual void onDisableVerificationRequirement(M24SR *nfc,
					StatusTypeDef status, PasswordType_t ){
				onFinishCommand(nfc,status);
			}

			virtual void onChangeReferenceData(M24SR *nfc, StatusTypeDef status,
					PasswordType_t type,
					uint8_t *){
				if(status==M24SR_SUCCESS)
					nfc->EnablePermanentState(type);
				else
					onFinishCommand(nfc,status);
			}

			virtual void onEnablePermanentState(M24SR *nfc, StatusTypeDef status,
					PasswordType_t ){
				onFinishCommand(nfc,status);
			}


		private:

			/**
			 * Remove the private callbacks and call the user callback.
			 * @param nfc Object triggering the command.
			 * @param status Command status.
			 */
			void onFinishCommand(M24SR *nfc,StatusTypeDef status){
				nfc->mComponentCallback=NULL;

				if(mEnable){
					if(mType==ReadPwd){
						nfc->getCallback()->onEnableReadPassword(nfc,status,mNewPwd);
					}else
						nfc->getCallback()->onEnableWritePassword(nfc,status,mNewPwd);
				}else{
					if(mType==ReadPwd){
						nfc->getCallback()->onDisableReadPassword(nfc,status);
					}else
						nfc->getCallback()->onDisableWritePassword(nfc,status);
				}//if-else enable
			}//onFinish

			const uint8_t *mNewPwd;
			PasswordType_t mType;
			bool mEnable;

		};


		/**
		 * Object containing the callback chain needed to change the password request
		 */
		ChangePasswordRequestStatusCallback mChangePasswordRequestStatusCallback;
		friend class ChangePasswordRequestStatusCallback;

		/**
		 * This class permits to disable all the password requests to read/write into the tag
		 * This class is equivalent to calling the methods:
		 * <ul>
		 *   <li> Verify(i2c) </li>
		 *   <li> DisablePermanentState(Read) </li>
		 *   <li> DisablePermanentState(write) </li>
		 *   <li> DisableVerificationRequirement(Read) </li>
		 *   <li> DisableVerificationRequirement(write) </li>
		 *   <li> ChangeReferenceData(Read) </li>
		 *   <li> ChangeReferenceData(write) </li>
		 * </ul>
		 */
		class RemoveAllPasswordCallback : public Callbacks{

			/**
			 * Store the default password used for open a super user session
			 * it will be set as default read/write password
			 */
			const uint8_t *mI2CPwd;

			public:

				/**
				 * Build the chain of callbacks.
				 */
				RemoveAllPasswordCallback():mI2CPwd(NULL){}

				virtual void onVerified(M24SR *nfc,StatusTypeDef status,
						PasswordType_t,const uint8_t* data){
					if(status!=M24SR_SUCCESS)
						return onFinishCommand(nfc,status);
					mI2CPwd = data;
					nfc->DisablePermanentState(ReadPwd);
				}

				virtual void onDisablePermanentState(M24SR *nfc , StatusTypeDef status,
						PasswordType_t type){
					if(status!=M24SR_SUCCESS)
						return onFinishCommand(nfc,status);
					if(type==ReadPwd)
						nfc->DisablePermanentState(WritePwd);
					else
						nfc->DisableVerificationRequirement(ReadPwd);
				}

				virtual void onDisableVerificationRequirement(M24SR *nfc ,
						StatusTypeDef status,PasswordType_t type){
					if(status!=M24SR_SUCCESS)
						return onFinishCommand(nfc,status);
					if(type==ReadPwd)
						nfc->DisableVerificationRequirement(WritePwd);
					else
						nfc->ChangeReferenceData(ReadPwd,mI2CPwd);
				}

				virtual void onChangeReferenceData(M24SR *nfc ,StatusTypeDef status,PasswordType_t type,
						uint8_t *data){
					if(status!=M24SR_SUCCESS)
						return onFinishCommand(nfc,status);
					if(type==ReadPwd)
						nfc->ChangeReferenceData(WritePwd,data);
					else
						onFinishCommand(nfc,status);
				}

			private:

				/**
				 * Remove the private callback and call the onDisableAllPassword callback.
				 * @param nfc Object triggering the command.
				 * @param status Command status.
				 */
				void onFinishCommand(M24SR *nfc,StatusTypeDef status){
					nfc->mComponentCallback=NULL;
					mI2CPwd=NULL;
					nfc->getCallback()->onDisableAllPassword(nfc,status);
				}//onFinish

		};


		/**
		 * Object containing the callback chain needed to remove the password request
		 */
		RemoveAllPasswordCallback mRemoveAllPasswordCallback;
		friend class RemoveAllPasswordCallback;

		/**
		 * This class permits to set the tag as read/write only
		 * This class is equivalent to calling the methods:
		 * <ul>
		 *   <li> Verify(i2c) </li>
		 *   <li> EnablePermanentState(Read/write) </li>
		 * </ul>
		 * or:
		 * <ul>
		 *   <li> Verify(i2c) </li>
		 *   <li> DisablePermanentState</li>
		 *   <li> DisableVerificationRequirement(Read/write) </li>
		 * </ul>
		 */
		class ChangeAccessStateCallback : public Callbacks{

			public:

				typedef enum{
					WRITE,
					READ
				}AccessType_t;

				/**
				 * Build the chain of callbacks.
				 */
				ChangeAccessStateCallback():mType(WRITE),mEnable(false){}

				/**
				 * Set the access to enable/disable an access type.
				 * @param type Access type.
				 * @param enable True to enable the state, False to disable it.
				 */
				void changeAccessState(AccessType_t type,bool enable){
					mType=type;
					mEnable=enable;
				}

				virtual void onVerified(M24SR *nfc,StatusTypeDef status,
						PasswordType_t,const uint8_t*){
					if(status!=M24SR_SUCCESS)
						return onFinishCommand(nfc,status);

					if(mEnable){
						nfc->DisablePermanentState(mType==WRITE? WritePwd : ReadPwd);
					}else
						nfc->EnablePermanentState(mType==WRITE? WritePwd : ReadPwd);

				}

				virtual void onDisablePermanentState(M24SR *nfc, StatusTypeDef status,
						PasswordType_t type ){
					if(status!=M24SR_SUCCESS)
						return onFinishCommand(nfc,status);

					nfc->DisableVerificationRequirement(type);
				}

				virtual void onDisableVerificationRequirement(M24SR *nfc , StatusTypeDef status,
						PasswordType_t ){
					onFinishCommand(nfc,status);
				}

				virtual void onEnablePermanentState(M24SR *nfc ,StatusTypeDef status,PasswordType_t ){
					onFinishCommand(nfc,status);
				}


			private:

				/**
				 * Remove the private callback and call the user callback.
				 * @param nfc Object triggering the command.
				 * @param status Command status.
				 */
				void onFinishCommand(M24SR *nfc,StatusTypeDef status){
					nfc->mComponentCallback=NULL;
					if(mEnable){
						if(mType==READ){
							//enable read = disable write only
							nfc->getCallback()->onDisableWriteOnly(nfc,status);
						}else
							//enable write = disable read only
							nfc->getCallback()->onDisableReadOnly(nfc,status);
					}else{
						if(mType==WRITE){
							//disable write = enable read only
							nfc->getCallback()->onEnableReadOnly(nfc,status);
						}else{
							//
							nfc->getCallback()->onEnableWriteOnly(nfc,status);
						}
					}//if-else enable
				}//onFinish

				AccessType_t mType;
				bool mEnable;

		};


		/**
		 * Object containing the callback chain needed to change the access state
		 */
		ChangeAccessStateCallback mChangeAccessStateCallback;
		friend class ChangeAccessStateCallback;


	/**
	 * Object with the callback used to send a ManageGPO command.
	 * This class is equivalent to calling the methods:
	 * <ul>
	 *   <li> SelectedApplication </li>
	 *   <li> SelectSystemfile </li>
	 *   <li> ReadBinar: read the old value </li>
	 *   <li> onVerified </li>
	 *   <li> onUpdatedBinary: write the new value</li>
	 * </ul>
	 */
	class ManageGPOCallback : public Callbacks{

	public:

		/**
		 * Build the chain of callbacks.
		 * @param parent Parent component to run the command on.
		 */
		ManageGPOCallback(M24SR &parent):mParent(parent),
				mGpoConfig(HIGH_IMPEDANCE),mReadGpoConfig(0),mI2CGpo(true){}


		/**
		 * Command parameters.
		 * @param i2cGpo true to change the i2c gpo, false for the rf gpo.
		 * @param newConfig new gpo function.
		 */
		void setNewGpoConfig(bool i2cGpo,NFC_GPO_MGMT newConfig){
			mGpoConfig=newConfig;
			mI2CGpo =i2cGpo;
		}

		virtual void onSelectedApplication(M24SR *nfc,StatusTypeDef status){
			if(status==M24SR_SUCCESS)
				nfc->SelectSystemfile();
			else
				onFinishCommand(nfc,status);
		}

		virtual void onSelectedSystemFile(M24SR *nfc,StatusTypeDef status){
			if(status==M24SR_SUCCESS)
				nfc->ReadBinary(0x0004, 0x01, &mReadGpoConfig);
			else
				onFinishCommand(nfc,status);
		}

		virtual void onReadByte(M24SR *nfc,StatusTypeDef status,
				uint16_t,uint8_t*, uint16_t ){
			if(status==M24SR_SUCCESS)
				nfc->Verify(M24SR::I2CPwd, 0x10, M24SR::DEFAULT_PASSWORD);
			else
				onFinishCommand(nfc,status);
		}

		virtual void onVerified(M24SR *nfc,StatusTypeDef status,PasswordType_t, const uint8_t*){
			if(status!=M24SR_SUCCESS)
				return onFinishCommand(nfc,status);

			if(mI2CGpo)
				mReadGpoConfig = (mReadGpoConfig & 0xF0) | (uint8_t)mGpoConfig;
			else
				mReadGpoConfig = (mReadGpoConfig & 0x0F) | (((uint8_t)mGpoConfig)<<4);

			nfc->UpdateBinary(0x0004, 0x01, &mReadGpoConfig);
		}

		virtual void onUpdatedBinary(M24SR *nfc,StatusTypeDef status,
				uint16_t , uint8_t*, uint16_t ){

			if(status==M24SR_SUCCESS){
				if (mGpoConfig == I2C_ANSWER_READY){
					mParent.mCommunicationType = ASYNC;
				}else{
					mParent.mCommunicationType = SYNC;
				}//if-else
			}//status
			onFinishCommand(nfc,status);
		}

	private:

		/**
		 * Remove the private callback and call the user callback.
		 * @param nfc Object where the command was send to.
		 * @param status Command status.
		 */
		void onFinishCommand(M24SR *nfc,StatusTypeDef status){
			mParent.mComponentCallback=NULL;
			if(mI2CGpo){
				mParent.mCallback->onManageI2CGPO(nfc,status,mGpoConfig);
			}else{
				mParent.mCallback->onManageRFGPO(nfc,status,mGpoConfig);
			}//if-else
		}//onFinishCommand

		/**
		 * Component where send the commands
		 */
		M24SR &mParent;

		/** new gpo function that this class has to write */
		NFC_GPO_MGMT mGpoConfig;

		/**
		 * variable where storeing the read gpo configuration
		 */
		uint8_t mReadGpoConfig;

		/**
		 * true to change the i2c gpo, false to change the rf gpo
		 */
		bool mI2CGpo;

	};

	/**
	 * Object containing the callback chain needed to change the gpo function
	 */
	ManageGPOCallback mManageGPOCallback;


	/**
	 * Object with the callback used to read the component ID
	 * This class is equivalent to calling the methods:
	 * <ul>
	 *   <li> SelectedApplication </li>
	 *   <li> SelectSystemfile </li>
	 *   <li> ReadBinary </li>
	 * </ul>
	 */
	class ReadIDCallback : public Callbacks{

	public:

		/**
		 * Build the chain of callbacks.
		 * @param parent object where to send the command to.
		 */
		ReadIDCallback(M24SR &parent):mParent(parent),mIdPtr(NULL){}

		/**
		 * Set the variable containing the result
		 * @param idPtr
		 */
		void readIdOn(uint8_t *idPtr){
			mIdPtr=idPtr;
		}

		virtual void onSelectedApplication(M24SR *nfc,StatusTypeDef status){
			if(status==M24SR_SUCCESS){
				nfc->SelectSystemfile();
			}else
				onFinishCommand(nfc,status);

		}

		virtual void onSelectedSystemFile(M24SR *nfc,StatusTypeDef status){
			if(status==M24SR_SUCCESS){
				nfc->ReadBinary(0x0011, 0x01, mIdPtr);
			}else
				onFinishCommand(nfc,status);
		}

		virtual void onReadByte(M24SR *nfc,StatusTypeDef status,
			uint16_t ,uint8_t *, uint16_t ){
			onFinishCommand(nfc,status);
		}

	private:

		/**
		 * Remove the private callback and call the user onReadId function.
		 * @param nfc Object where the command was send.
		 * @param status Command status.
		 */
		void onFinishCommand(M24SR *nfc,StatusTypeDef status){
			mParent.mComponentCallback=NULL;
			mParent.getCallback()->onReadId(nfc,status,mIdPtr);
		}

		M24SR& mParent;

		/**
		 * pointer to read id
		 */
		uint8_t *mIdPtr;
	};


	/**
	 * Object containing the callback chain needed to read the component id
	 */
	ReadIDCallback mReadIDCallback;
	friend class ReadIDCallback;

	/**
	 * Convert a generic enum to the value used by the M24SR chip.
	 * @param type Password type.
	 * @return equivalent value used inside the m24sr chip */
	uint16_t passwordTypeToConst(const PasswordType_t &type)const{
		switch(type){
			case ReadPwd:
				return READ_PWD;
			case WritePwd:
				return WRITE_PWD;
			case I2CPwd:
			default:
				return I2C_PWD;
		}//switch
	}//passwordTypeToConst
	
	/**
	 * convert  a uint16 into an enum value
	 * @param type
	 * @return
	 */
	PasswordType_t constToPasswordType(const uint16_t type)const{
		switch(type){
			case READ_PWD:
				return ReadPwd;
			case WRITE_PWD:
				return WritePwd;
			case I2C_PWD:
			default:
				return I2CPwd;
		}//switch
	}//passwordTypeToConst
};

#endif // __M24SR_CLASS_H

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

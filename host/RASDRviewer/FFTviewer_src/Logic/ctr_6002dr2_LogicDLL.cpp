// -----------------------------------------------------------------------------
// FILE: 		ctr_6002dr2_LogicDLL.cpp
// DESCRIPTION:	ctr_6002dr2_Logic DLL API
// DATE:		2013-08-27
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

/**
	@defgroup Application_Level_functions Application level functions
	@defgroup ConnectionManager  Connection Manager
	@defgroup TopModule Top module
	@defgroup TxPLL TxPLL module
	@defgroup RxPLL RxPLL module
	@defgroup TxLPF TxLPF module
	@defgroup TxRF TxRF module
	@defgroup RxLPF	RxLPF module
	@defgroup RxVGA2 RxVGA2 module
	@defgroup RxFE RxFE module
	@defgroup ADDC ADDC module
	@defgroup Board Board module
	@defgroup Testing Testing module
*/

#include "ctr_6002dr2_LogicDLL.h"
#include "Main_Module.h"
#include "ConnectionManager.h"
#include "TestingModule.h"
#include "Packets.h"
class Main_Module;
Main_Module *mainModule = NULL;
//==============================================================================
// Application level commands
//==============================================================================

/// makes sure that main module is initialized
Main_Module* getMainModule()
{
	if(mainModule == NULL)
	{
		mainModule = new Main_Module();
		getMainModule()->initialize();
	}
	return mainModule;
}

extern "C"
{
// Main Module
/**
	@ingroup Application_Level_functions

	@brief Set pointer to callback function, that will be used to signal about message log updates, data changes and chip connection status.
	@param pCallbackFunction pointer to static function that takes two parameters:
	integer as update code, and pointer to char array as additional parameters for that code.
*/
CTR_6002DR2_API void LMAL_MainSetCallbackInterfaceUpdate(void (*pCallbackFunction)(int, char*) )
{
	getMainModule()->updateInterfaceCallback = pCallbackFunction;
}

/**
	@ingroup Application_Level_functions

	@brief Initializes all control modules and connection manager, searches for connected chips and connects to the first one found.
	@return 1-succeeded, 0-failed.
*/
CTR_6002DR2_API int LMAL_Initialize()
{
	getMainModule()->initialize();
	return 1;
}

/**
	@ingroup Application_Level_functions

	@brief Loads default configuration and prepares to create a new file containing all chip parameters.
*/
CTR_6002DR2_API void LMAL_MainFileNewExecute()
{
	getMainModule()->FileNewExecute();
}

/**
	@ingroup Application_Level_functions

	@brief Saves current chip configuration to given file.
	@param link filename or full path to file.
*/
CTR_6002DR2_API void LMAL_MainFileSaveAs(char* link)
{
	getMainModule()->FileSaveAs(link);
}

/**
	@ingroup Application_Level_functions

	@brief Saves changes to currently used project file.
*/
CTR_6002DR2_API void LMAL_MainFileSave()
{
	getMainModule()->FileSave();
}

/**
	@ingroup Application_Level_functions
	@brief Reads version, revision and mask from the chip.
	@param &ver reference to chip version.
	@param &rev reference to chip revision.
	@param &mask reference to chip mask.
*/
CTR_6002DR2_API void LMAL_GetVerRevMask(int &ver, int &rev, int &mask)
{
	getMainModule()->getVerRevMask(ver, rev, mask);
}

/**
	@ingroup Application_Level_functions

	@brief Reads all configuration from the chip and updates user interface according to it.
*/
CTR_6002DR2_API void LMAL_MainReadSettingsFromChip()
{
	getMainModule()->MatchGUIToChip();
}

/**
	@ingroup Application_Level_functions

	@brief Sets configuration sending mode to automatic or manual.

	When automatic mode is	selected every parameter change will be immediately sent to the chip, when in manual
	mode, configuration will be sent only when LMAL_MainDownload() is called.
	@param state true - automatic, false - manual.
*/
CTR_6002DR2_API void LMAL_MainSetAutoDownload(bool state)
{
	getMainModule()->setAutoDownload(state);
}

/**
	@ingroup Application_Level_functions

	@brief Sends all configuration to the chip.
*/
CTR_6002DR2_API void LMAL_MainDownload()
{
	getMainModule()->Download();
}

/**
	@ingroup Application_Level_functions

	@brief Opens project file containing all chip configuration parameters.
	@param filename filename or full path to file.
*/
CTR_6002DR2_API void LMAL_MainOpenFile(char *filename)
{
	getMainModule()->LoadConfiguration(filename);
}

/**
	@ingroup Application_Level_functions

	@brief Sets reference clock
	@param refClk_Hz reference clock in Hz.
*/
CTR_6002DR2_API void LMAL_SetReferenceClock(double refClk_Hz)
{
	getMainModule()->setRefClk(refClk_Hz);
}

/**
	@ingroup Application_Level_functions

	@brief Returns reference clock.
	@return reference clock in Hz.
*/
CTR_6002DR2_API double LMAL_GetReferenceClock()
{
	return  getMainModule()->getRefClk();
}
/**
	@ingroup Application_Level_functions
	@brief Calibrates Tx modules.
*/
CTR_6002DR2_API void LMAL_CalibrateTx()
{
	getMainModule()->Cust_CalibrateTx();
}
/**
	@ingroup Application_Level_functions
	@brief Calibrates Rx modules.
*/
CTR_6002DR2_API void LMAL_CalibrateRx()
{
	getMainModule()->Cust_CalibrateRx();
}

/**
	@ingroup Application_Level_functions
	@brief Sets active LNA.
	@param index active lna
	- 0 : all LNA's disabled
	- 1 : LNA1 active
	- 2 : LNA2 active
	- 3 : LNA3 active.
*/
CTR_6002DR2_API void LMAL_SelectActiveLNA(int index)
{
	getMainModule()->Cust_setLNASEL(index);
}

/**
	@ingroup Application_Level_functions
	@brief Sets Rx bypass mode
	@param index bypass mode
	- 0 : normal operation
	- 1 : bypass RxLPF
	- 2 : bypass RxLPF, RxVGA2
*/
CTR_6002DR2_API void LMAL_SetRxBypass(int index)
{
	getMainModule()->Cust_setRxBypass(index);
}

/**
	@ingroup Application_Level_functions
	@brief Sets Tx bypass mode.
	@param index bypass mode
	- 0 : normal operation
	- 1 : bypass TxLPF
*/
CTR_6002DR2_API void LMAL_SetTxBypass(int index)
{
	getMainModule()->Cust_setTxBypass(index);
}

/**
	@ingroup Application_Level_functions
	@brief Sets RF / BB loopback mode
	@param index value index from the list
	- 0-normal operation,
	- 1-BB loopback to RxLPF input,
	- 2-BB loopback to RxVGA2 input,
	- 3-BB loopback to output pins,
	- 4-RF loopback LNA1,
	- 5-RF loopback LNA2,
	- 6-RF loopback LNA3,

*/
CTR_6002DR2_API void LMAL_SetLoopback(int index)
{
	getMainModule()->Cust_setLoopback(index);
}

/**
	@ingroup Application_Level_functions
	@brief Selects DLTX band from band list
	@param index index of band from bands list that is received from LMAL_MainGetDLTXBands()
*/
CTR_6002DR2_API void LMAL_MainSetDLTXBand(int index)
{
	getMainModule()->Cust_setDLTXBand(index);
}

/**
	@ingroup Application_Level_functions
	@brief Selects DLTX channel from channels list
	@param index index of channel from channels list that is received from LMAL_MainGetDLTXChannels()
*/
CTR_6002DR2_API void LMAL_MainSetDLTXChannel(int index)
{
	getMainModule()->Cust_setDLTXChannel(index);
}
/**
	@ingroup Application_Level_functions
	@brief Selects ULRX band from band list
	@param index index of band from bands list that is received from LMAL_MainGetULRXBands()
*/
CTR_6002DR2_API void LMAL_MainSetULRXBand(int index)
{
	getMainModule()->Cust_setULRXBand(index);
}
/**
	@ingroup Application_Level_functions
	@brief Selects ULRX channel from channels list
	@param index index of channel from channels list that is received from LMAL_MainGetULRXChannels()
*/
CTR_6002DR2_API void LMAL_MainSetULRXChannel(int index)
{
	getMainModule()->Cust_setULRXChannel(index);
}

// get bands and channels
// -----------------------
/**
	@ingroup Application_Level_functions

	@brief Returns DLTX frequency.
	@return DLTX frequency in Hz.
*/
CTR_6002DR2_API double LMAL_MainGetDLTXFreq()
{
	return getMainModule()->Cust_getDLTXFreq();
}
/**
	@ingroup Application_Level_functions

	@brief Returns ULRX frequency.
	@return ULRX frequency in Hz.
*/
CTR_6002DR2_API double LMAL_MainGetULRXFreq()
{
	return getMainModule()->Cust_getULRXFreq();
}

/**
	@ingroup Application_Level_functions

	@brief Returns array of c-strings containing available DLTX band names.
	@param bands pointer to array of c-strings where to copy results.
	@param count returns number of c-strings returned.
*/
CTR_6002DR2_API void LMAL_MainGetDLTXBands(char** bands, int &count)
{
	int cnt = 0;
	const string *str = NULL;
	str = getMainModule()->Cust_getDLTXBands(cnt);

	if(bands == NULL)
	{
		count = cnt;
		return;
	}
	for( int i=0; i<cnt; i++)
	{
		memset(bands[i], 0, str[i].length()+1);
		memcpy(bands[i], str[i].c_str(), str[i].length());
	}
	count = cnt;
	//delete str;
}

/**
	@ingroup Application_Level_functions

	@brief Returns array of c-strings containing available ULRX band names.
	@param bands pointer to array of c-strings where to copy results.
	@param count returns number of c-strings returned.
*/
CTR_6002DR2_API void LMAL_MainGetULRXBands(char** bands, int &count)
{
	int cnt = 0;
	const string *str = NULL;
	str = getMainModule()->Cust_getULRXBands(cnt);
	if(bands == NULL)
	{
		count = cnt;
		return;
	}
	for( int i=0; i<cnt; i++)
	{
		memset(bands[i], 0, str[i].length()+1);
		memcpy(bands[i], str[i].c_str(), str[i].length());
	}
	count = cnt;
	//delete str;
}

/**
	@ingroup Application_Level_functions

	@brief Returns array of c-strings containing available DLTX channel names.
	@param channels pointer to array of c-strings where to copy results.
	@param count returns number of c-strings returned.
*/
CTR_6002DR2_API void LMAL_MainGetDLTXChannels(char** channels, int &count)
{
	int cnt = 0;
	const string *str = NULL;
	str = getMainModule()->Cust_getDLTXChannels(cnt);
	if(channels == NULL)
	{
		count = cnt;
		return;
	}
	for( int i=0; i<cnt; i++)
	{
		memset(channels[i], 0, str[i].length()+1);
		memcpy(channels[i], str[i].c_str(), str[i].length());
	}
	count = cnt;
}

/**
	@ingroup Application_Level_functions

	@brief Returns array of c-strings containing available ULRX channel names.
	@param channels pointer to array of c-strings where to copy results.
	@param count returns number of c-strings returned.
*/
CTR_6002DR2_API void LMAL_MainGetULRXChannels(char** channels, int &count)
{
	int cnt = 0;
	const string *str = NULL;
	str = getMainModule()->Cust_getULRXChannels(cnt);
	if(channels == NULL)
	{
		count = cnt;
		return;
	}
	for( int i=0; i<cnt; i++)
	{
		memset(channels[i], 0, str[i].length()+1);
		memcpy(channels[i], str[i].c_str(), str[i].length());
	}
	count = cnt;
}

/**
	@ingroup Application_Level_functions
	@brief Calibrates LPF core.
*/
CTR_6002DR2_API void LMAL_CalibrateLPFCore()
{
	getMainModule()->CalLPFCore();
}

/**
	@ingroup Application_Level_functions

	@brief Runs registers test
	@retval false test failed
	@retval true test passed
*/
CTR_6002DR2_API bool LMAL_TestRegisters()
{
	return getMainModule()->TestRegisters();
}

/**
	@ingroup Application_Level_functions

	@brief Sets currently used project filename.
	@param filename project name
*/
CTR_6002DR2_API void LMAL_MainSetCurrentFileName(const char *filename)
{
	getMainModule()->setCurrentFileName(filename);
}

/**
	@ingroup Application_Level_functions

	@brief Enables all SPI clocks
*/
CTR_6002DR2_API void LMAL_EnableAllSPIClocks()
{
	getMainModule()->EnableAllSPIClocks();
}

/**
	@ingroup Application_Level_functions

	@brief Restores SPI clocks to state that was before LMAL_EnableAllSPIClocks();
*/
CTR_6002DR2_API void LMAL_RestoreAllSPIClocks()
{
	getMainModule()->RestoreAllSPIClocks();
}

/**
	@ingroup Application_Level_functions

	@brief Restores SPI clock bufer states according to GUI settings
*/
CTR_6002DR2_API void LMAL_MainCompareChipToGUI()
{
	getMainModule()->CompareChipToGUI();
}

/**
	@ingroup Application_Level_functions

	@brief Reads configuration from the chip, then writes current GUI settings and current chip settings into file.
*/
CTR_6002DR2_API void LMAL_MainReadConfiguration(char *filename)
{
	getMainModule()->ReadConfiguration(filename);
}

/**
	@ingroup Application_Level_functions

	@brief Saves configuration to file under RVF format.
	@param filename Filename or full path to file.
	@param dec = 1 if format is decimal, dec = 0 if format is hexadecimal;
*/
CTR_6002DR2_API void LMAL_MainSaveUnderRVF_Format(const char *filename, int dec)
{
	getMainModule()->SaveUnderRVF_Format(filename, dec);
}

/**
	@ingroup Application_Level_functions

	@brief Saves chip configuration to file using FRIF format.
	@param filename Filename or full path to file.
	@param rfifParam rfif parameter
*/
CTR_6002DR2_API void LMAL_MainSaveUnderRFIF_Format(const char *filename, int rfifParam)
{
	getMainModule()->SaveUnderRFIF_Format(filename, rfifParam);
}

/**
	@ingroup Application_Level_functions

	@brief Saves all registers to file.
	@param filename filename or full path to file.
*/
CTR_6002DR2_API void LMAL_MainSaveRegisters(const char *filename)
{
	getMainModule()->SaveRegisters(filename);
}

/**
	@ingroup Application_Level_functions

	@brief Returns main message log size.
	@return main message log length in bytes
*/
CTR_6002DR2_API unsigned int LMAL_MainGetMessageLogLength()
{
	return getMainModule()->messagesLog.Length();
}

/**
	@ingroup Application_Level_functions

	@brief Copies main message log to supplied buffer
	@param buffer pointer to array, array must be big enough to fix all data, required size can be obtained from LMAL_MainGetMessageLogLength()
*/
CTR_6002DR2_API void LMAL_MainGetMessageLogMessages(char *buffer)
{
	getMainModule()->messagesLog.Dump(buffer);
}

/**
	@ingroup Application_Level_functions

	@brief Returns register test log size.
	@return register test message log length in bytes
*/
CTR_6002DR2_API unsigned int LMAL_MainRegTestGetLogLength()
{
	return getMainModule()->dRegTest->Length();
}

/**
	@ingroup Application_Level_functions

	@brief Copies registers test message log to supplied buffer
	@param buffer pointer to array, array must be big enough to fix all data, required size can be obtained from LMAL_MainRegTestGetLogLength()
*/
CTR_6002DR2_API void LMAL_MainRegTestGetLogMessages(char *buffer)
{
	getMainModule()->dRegTest->Dump(buffer);
}

/**
	@ingroup Application_Level_functions
	@brief Deallocates memory used by the library.
*/
CTR_6002DR2_API void LMAL_Quit()
{
	if(mainModule)
		delete mainModule;
	mainModule = NULL;
}

//==============================================================================
// End of Main Module

//==============================================================================
// Low level commands
//==============================================================================

// TxRf Module
//==============================================================================
/**
	@ingroup TxRF
	@brief Returns TxRf module address.
	@return TxRf module address.
*/
CTR_6002DR2_API char LMLL_TxRfGetAddr()
{
	return  getMainModule()->getTxRf()->getAddr();
}

/**
	@ingroup TxRF
	@brief Enables or disables TxRF modules
	@param enabled set true to enable
*/
CTR_6002DR2_API void LMLL_TxRfSetPwrTxRfMods(bool enabled)
{
	getMainModule()->getTxRf()->setPwrTxRfMods(enabled);
}

/**
	@ingroup TxRF
	@brief Returns state of TxRF module.
	@return state of TxRF module.
	@retval true enabled
	@retval false disabled
*/
CTR_6002DR2_API bool LMLL_TxRfGetPwrTxRfMods()
{
	return  getMainModule()->getTxRf()->getPwrTxRfMods();
}

/**
	@ingroup TxRF
	@brief Sets TxRf decode mode.
	@param index of value from list
	- 0 : decode control signals
	- 1 : use control signals from test mode registers
*/
CTR_6002DR2_API void LMLL_TxRfSetDecode(int index)
{
	getMainModule()->getTxRf()->setDecode(index);
}

/**
	@ingroup TxRF
	@brief returns TxRf decode mode.
	@retval 0 decode control signals
	@retval 1 use control signals from test mode registers
*/
CTR_6002DR2_API int LMLL_TxRfGetDecode()
{
	return  getMainModule()->getTxRf()->getDecode();
}

/**
	@ingroup TxRF
	@brief Sets TxRf VGA1 Gain, dB
	@param index index of value from list
	- 0 : -35 dB
	- 1 : -34 dB
	- ...
	- 21 : -14 dB
	- ...
	- 31 : -4 dB
*/
CTR_6002DR2_API void LMLL_TxRfSetVga1G_u(int index)
{
	getMainModule()->getTxRf()->setVga1G_u(index);
}

/**
	@ingroup TxRF
	@brief Returns TxRf VGA1 Gain
	@retval 0 : -35 dB
	@retval 1 : -34 dB
	@retval	...
	@retval	21 : -14 dB
	@retval	...
	@retval	31 : -4 dB
*/
CTR_6002DR2_API int LMLL_TxRfGetVga1G_u()
{
	return  getMainModule()->getTxRf()->getVga1G_u();
}

/**
	@ingroup TxRF
	@brief Sets TxVGA1 DC shift control, LO leakage cancellation.
	@param index index of value from list
	- 0 : -16 mV
	- 1 : -15.875 mv
	- ...
	- 127 : -0.125 mV
	- 128 : 0 mV
	- 129 : 0.125 mV
	- ...
	- 255 : 15.875 mV
*/
CTR_6002DR2_API void LMLL_TxRfSetVga1DcI(int index)
{
	getMainModule()->getTxRf()->setVga1DcI(index);
}

/**
	@ingroup TxRF
	@brief Returns TxVGA1 DC shift control, LO leakage cancellation.
	@return index of value from list
	@retval 0 : -16 mV
	@retval 1 : -15.875 mV
	@retval ...
	@retval 255 : 15.875 mV
*/
CTR_6002DR2_API int LMLL_TxRfGetVga1DcI()
{
	return  getMainModule()->getTxRf()->getVga1DcI();
}

/**
	@ingroup TxRF
	@brief Sets TxVGA1 DC shift control, LO leakage cancellation.
	@param index index of value from list
	- 0 : -16 mV
	- 1 : -15.875 mv
	- ...
	- 127 : -0.125
	- 128 : 0
	- 129 : 0.125
	- ...
	- 255 : 15.875
*/
CTR_6002DR2_API void LMLL_TxRfSetVga1DcQ(int index)
{
	getMainModule()->getTxRf()->setVga1DcQ(index);
}

/**
	@ingroup TxRF
	@brief Returns TxVGA1 DC shift control, LO leakage cancellation.
	@return index of value from list
	@retval 0 : -16 mV
	@retval 1 : -15.875 mv
	@retval ...
	@retval 127 : -0.125
	@retval 128 : 0
	@retval 129 : 0.125
	@retval ...
	@retval 255 : 15.875
*/
CTR_6002DR2_API int LMLL_TxRfGetVga1DcQ()
{
	return  getMainModule()->getTxRf()->getVga1DcQ();
}

/**
	@ingroup TxRF
	@brief Sets VGA2 power amplifier (TX output) selection.
	@param index
	- 0 : PA1-OFF PA2-OFF
	- 1 : PA1-ON  PA2-OFF
	- 2 : PA1-OFF PA2-ON
	- 3 : PA1-OFF PA2-OFF
*/
CTR_6002DR2_API void LMLL_TxRfSetPA(int index)
{
	getMainModule()->getTxRf()->setPA(index);
}

/**
	@ingroup TxRF
	@brief Returns VGA2 power amplifier selection.
	@retval 0 : PA1-OFF PA2-OFF
	@retval 1 : PA1-ON  PA2-OFF
	@retval 2 : PA1-OFF PA2-ON
	@retval 3 : PA1-OFF PA2-OFF
*/
CTR_6002DR2_API int LMLL_TxRfGetPA()
{
	return  getMainModule()->getTxRf()->getPA();
}

/**
	@ingroup TxRF
	@brief Sets TXVGA2 gain
	@param index value index from the list
	- 0 : 0 dB (default)
	- 1 : 1 dB
	- ...
	- 25 : 25 dB
	- 26 : 25 dB
	- ...
	- 31 : 25
*/
CTR_6002DR2_API void LMLL_TxRfSetVga2G_u(int index)
{
	getMainModule()->getTxRf()->setVga2G_u(index);
}

/**
	@ingroup TxRF
	@brief Returns TXVGA2 gain
	@retval 0 : 0 dB
	@retval 1 : 1 dB
	@retval ...
	@retval 25 : 25 dB
*/
CTR_6002DR2_API int LMLL_TxRfGetVga2G_u()
{
	return  getMainModule()->getTxRf()->getVga2G_u();
}

/**
	@ingroup TxRF
	@brief Enables or diables VGA1 I channel power.
	@param state power state
	- 0 : powered down
	- 1 : powered up (default)
*/
CTR_6002DR2_API void LMLL_TxRfSetPwrVga1_I(bool state)
{
	getMainModule()->getTxRf()->setPwrVga1_I(state);
}

/**
	@ingroup TxRF
	@brief Returns whether VGA1 I channel is enabled or disabled.
	@retval 0 : powered down
	@retval 1 : powered up (default)
*/
CTR_6002DR2_API bool LMLL_TxRfGetPwrVga1_I()
{
	return  getMainModule()->getTxRf()->getPwrVga1_I();
}

/**
	@ingroup TxRF
	@brief Sets power down state for TXMIX.
	@param state
	- 0 : powered up
	- 1 : powered down (MIX and VGA2 disabled)
*/
CTR_6002DR2_API void LMLL_TxRfSetPwrVga2(bool state)
{
	getMainModule()->getTxRf()->setPwrVga2(state);
}

/**
	@ingroup TxRF
	@brief Returns power down state for TXMIX.
	@retval 0 : powered up
	@retval 1 : powered down (MIX and VGA2 disabled)
*/
CTR_6002DR2_API bool LMLL_TxRfGetPwrVga2()
{
	return  getMainModule()->getTxRf()->getPwrVga2();
}

/**
	@ingroup TxRF
	@brief Sets TXVGA1 gain, raw access.
	@param index value index from the list
	- 0 : -35 dB
	- 1 : -34 dB
	- ...
	- 21 : -14 dB (default)
	- ...
	- 30 : -5 dB
	- 31 : -4 dB
*/
CTR_6002DR2_API void LMLL_TxRfSetVga1G_t(int index)
{
	getMainModule()->getTxRf()->setVga1G_t(index);
}

/**
	@ingroup TxRF
	@brief Returns TXVGA1 gain, raw access.
	@retval 0 : -35 dB
	@retval 1 : -34 dB
	@retval ...
	@retval 21 : -14 dB (default)
	@retval ...
	@retval 30 : -5 dB
	@retval 31 : -4 dB
*/
CTR_6002DR2_API int LMLL_TxRfGetVga1G_t()
{
	return  getMainModule()->getTxRf()->getVga1G_t();
}

/**
	@ingroup TxRF
	@brief Sets the gain of PA1, PA2 and AUXPA.
	@param index value to calculate gain, Gain=20*log10(0.038*index[8:0])

	Raw access for PA1, PA2: Gain=20*log10(0.038*index[8:0])
	For AUXPA: Only 4 LSB's are used, max gain ~22dB
	default: 0
*/
CTR_6002DR2_API void LMLL_TxRfSetVga2G_t(int index)
{
	getMainModule()->getTxRf()->setVga2G_t(index);
}

/**
	@ingroup TxRF
	@brief Returns value used to calculate gain for PA1, PA2 and AUXPA.
	@return value used to calculate gain  Gain=20*log10(0.038*value[8:0])
*/
CTR_6002DR2_API int LMLL_TxRfGetVga2G_t()
{
	return  getMainModule()->getTxRf()->getVga2G_t();
}

/**
	@ingroup TxRF
	@brief Enables or diables VGA1 Q channel power.
	@param state power state
	- 0 : powered down
	- 1 : powered up (default)
*/
CTR_6002DR2_API void LMLL_TxRfSetPwrVga1_Q(bool state)
{
	getMainModule()->getTxRf()->setPwrVga1_Q(state);
}

/**
	@ingroup TxRF
	@brief Returns whether VGA1 Q channel is enabled or disabled.
	@retval 0 : powered down
	@retval 1 : powered up (default)
*/
CTR_6002DR2_API bool LMLL_TxRfGetPwrVga1_Q()
{
	return  getMainModule()->getTxRf()->getPwrVga1_Q();
}

/**
	@ingroup TxRF
	@brief Sets base band loop back switches control.
	@param index index of value from list
	- 0 : All switched open.
	- 1 : provides TXLPF output to base band loop back
	- 2 : provides TXVGA1 output to base band loop back
	- 3 : provides envelop/peak detector output to base band loop back.
*/
CTR_6002DR2_API void LMLL_TxRfSetLOOPBBEN(int index)
{
	getMainModule()->getTxRf()->setLOOPBBEN(index);
}

/**
	@ingroup TxRF
	@brief Returns base band loop back switches control.
	@retval 0 : All switched open.
	@retval 1 : provides TXLPF output to base band loop back
	@retval 2 : provides TXVGA1 output to base band loop back
	@retval 3 : provides envelop/peak detector output to base band loop back.
*/
CTR_6002DR2_API int LMLL_TxRfGetLOOPBBEN()
{
	return  getMainModule()->getTxRf()->getLOOPBBEN();
}

/**
	@ingroup TxRF
	@brief Sets AUXPA, auxiliary (RF loop back) PA power down.
	@param state power down state
	- 0 : powered up
	- 1 : powered down

	(available in test mode only) mask set v0, not used in v1.
*/
CTR_6002DR2_API void LMLL_TxRfSetPD_DRVAUX(bool state)
{
	getMainModule()->getTxRf()->setPD_DRVAUX(state);
}

/**
	@ingroup TxRF
	@brief Returns AUXPA, auxiliary (RF loop back) PA power down state.
	@retval 0 : powered up
	@retval 1 : powered down
*/
CTR_6002DR2_API bool LMLL_TxRfGetPD_DRVAUX()
{
	return  getMainModule()->getTxRf()->getPD_DRVAUX();
}

/**
	@ingroup TxRF
	@brief Sets power down for envelop/peak detectors.
	@param state powerd down state
	- 0 : powered up
	- 1 : powered down

	(available in test mode only) mask set v0, not used in v1.
*/
CTR_6002DR2_API void LMLL_TxRfSetPD_PKDET(bool state)
{
	getMainModule()->getTxRf()->setPD_PKDET(state);
}

/**
	@ingroup TxRF
	@brief Returns power down state for envelop/peak detectors.
	@retval 0 : powered up
	@retval 1 : powered down
*/
CTR_6002DR2_API bool LMLL_TxRfGetPD_PKDET()
{
	return  getMainModule()->getTxRf()->getPD_PKDET();
}

/**
	@ingroup TxRF
	@brief Sets envelop/peak detector analogue MUX, Detector select, MUX provides
	@param index value index from the list
	- 0 : AUXPA envelop detector output (default)
	- 1 : AUXPA peak detector output
	- 2 : PA1 envelop detector output
	- 3 : PA2 envelop detector output
*/
CTR_6002DR2_API void LMLL_TxRfSetENVD(int index)
{
	getMainModule()->getTxRf()->setENVD(index);
}

/**
	@ingroup TxRF
	@brief Returns envelop/peak detector analogue MUX, Detector select, MUX provides
	@retval 0 : AUXPA envelop detector output (default)
	@retval 1 : AUXPA peak detector output
	@retval 2 : PA1 envelop detector output
    @retval 3 : PA2 envelop detector output
*/
CTR_6002DR2_API int LMLL_TxRfGetENVD()
{
	return  getMainModule()->getTxRf()->getENVD();
}

/**
	@ingroup TxRF
	@brief Sets the signal for AC coupling, MUX provides.
	@param index value index from the list
	- 0 : reference DC generated inside the selected detector (default)
	- 1 : average of the selected detector output.
*/
CTR_6002DR2_API void LMLL_TxRfSetENVD2(int index)
{
	getMainModule()->getTxRf()->setENVD2(index);
}

/**
	@ingroup TxRF
	@brief Returns the signal for AC coupling, MUX provides.
	@retval 0 : reference DC generated inside the selected detector (default)
	@retval 1 : average of the selected detector output.
*/
CTR_6002DR2_API int LMLL_TxRfGetENVD2()
{
	return  getMainModule()->getTxRf()->getENVD2();
}

/**
	@ingroup TxRF
	@brief Sets the bandwidth of the envelop and peak detectors
	@param index value index from the list
	- 0 : Minimum bandwidth, envelop ~1MHz, peak 30kHz (default)
	- ...
	- 15 : Maximum bandwidth, envelop ~15MHz, peak ~300KHz
*/
CTR_6002DR2_API void LMLL_TxRfSetPKDBW(int index)
{
	getMainModule()->getTxRf()->setPKDBW(index);
}

/**
	@ingroup TxRF
	@brief Returns bandwidth of the envelop and peak detectors.
	@retval 0 : Minimum bandwidth, envelop ~1MHz, peak 30kHz
	@retval ...
	@retval 15 : Maximum bandwidth, envelop ~15MHz, peak ~300KHz
*/
CTR_6002DR2_API int LMLL_TxRfGetPKDBW()
{
	return  getMainModule()->getTxRf()->getPKDBW();
}

/**
	@ingroup TxRF
	@brief Shorts the resistor in the envelop/peak detector to speed up charging for faster response.

	After the initial charge up, it should be disabled to achieve a LPF function.
	@param state
	- 0 : switch open, LPF function in effect (default)
	- 1 : resistor shorted (no LPF function)
*/
CTR_6002DR2_API void LMLL_TxRfSetFST_PKDET(bool state)
{
	getMainModule()->getTxRf()->setFST_PKDET(state);
}

/**
	@ingroup TxRF
	@brief Returns state of resistor in the envelop/peak detector
	@retval 0 : switch open, LPF function in effect (default)
	@retval 1 : resistor shorted (no LPF function)
*/
CTR_6002DR2_API bool LMLL_TxRfGetFST_PKDET()
{
	return  getMainModule()->getTxRf()->getFST_PKDET();
}

/**
	@ingroup TxRF
	Bias stage of high frequency TX part has large resistors to filter the noise.
	However, they create large settling time. This switch can be used to short
	those resistors during the initialization and then it may be needed to open
	it to filter the noise, in case the noise is too high.
	@param state stateDesc
	- 0 : switch open (noise filtering functional)
	- 1 : resistors shorted (short settling - no noise filtering)
*/
CTR_6002DR2_API void LMLL_TxRfSetFST_TXHFBIAS(bool state)
{
	getMainModule()->getTxRf()->setFST_TXHFBIAS(state);
}

/**
	@ingroup TxRF
	Returns FST_TXHFBIAS
	@retval 0 : switch open (noise filtering functional) (default)
	@retval 1 : resistors shorted (short settling - no noise filtering)
*/
CTR_6002DR2_API bool LMLL_TxRfGetFST_TXHFBIAS()
{
	return  getMainModule()->getTxRf()->getFST_TXHFBIAS();
}

/**
	@ingroup TxRF
	@brief Sets the bias current of the LO buffer

	Higher current will increase the linearity. LSB=5/6mA.
	@param index value index from the list
	- 0 : minimum current
	- 1 : 5/6 mA
	- ...
	- 6 : TXMIX takes 5mA for buffer
	- 15 : maximum current
*/
CTR_6002DR2_API void LMLL_TxRfSetICT_TXLOBUF(int index)
{
	getMainModule()->getTxRf()->setICT_TXLOBUF(index);
}

/**
	@ingroup TxRF
	@brief Returns the bias current of the LO buffer
	@retval 0 : minimum current
	@retval 1 : 5/6 mA
	@retval ...
	@retval 6 : TXMIX takes 5mA for buffer
	@retval ...
	@retval 15 : maximum current
*/
CTR_6002DR2_API int LMLL_TxRfGetICT_TXLOBUF()
{
	return  getMainModule()->getTxRf()->getICT_TXLOBUF();
}

/**
	@ingroup TxRF
	The linearity of PAs depends on the bias at the base of the cascode npn's in the PA cells. Increasing the VBCAS will lower the base of the cascode npn.
	@param index value index from the list
	- 0 : maximum base voltage(default)
	- ...
	- 15 : minimum base voltage
*/
CTR_6002DR2_API void LMLL_TxRfSetVBCAS_TXDRV(int index)
{
	getMainModule()->getTxRf()->setVBCAS_TXDRV(index);
}

/**
	@ingroup TxRF
	Returns VBCAS_TXDRV
	@retval 0 : maximum base voltage
	@retval ...
	@retval 15 : minimum base voltage
*/
CTR_6002DR2_API int LMLL_TxRfGetVBCAS_TXDRV()
{
	return  getMainModule()->getTxRf()->getVBCAS_TXDRV();
}

/**
	@ingroup TxRF
	@brief Sets the bias current of the mixer.

	Higher current will increase the linearity. LSB=1mA.
	@param index value index from the list
	- 0 : 0 mA
	- 1 : 1 mA
	- ...
	- 12 : TXMIX takes 12mA for each cell (default)
	- ...
	- 31 : 31 mA
*/
CTR_6002DR2_API void LMLL_TxRfSetICT_TXMIX(int index)
{
	getMainModule()->getTxRf()->setICT_TXMIX(index);
}

/**
	@ingroup TxRF
	@brief Returns the bias current of the mixer.
	@retval 0 : 0 mA
	@retval 1 : 1 mA
	@retval ...
	@retval 12 : TXMIX takes 12mA for each cell (default)
	@retval ...
	@retval 31 : 31 mA
*/
CTR_6002DR2_API int LMLL_TxRfGetICT_TXMIX()
{
	return  getMainModule()->getTxRf()->getICT_TXMIX();
}


/**
	@ingroup TxRF
	@brief Sets the bias current of the PAs.

	Higher current will increase the linearity.
	@param index value index from the list
	- 0 : 0 mA
	- 1 : 1 mA
	- ...
	- 12 : PAs take 12mA for each cell (default)
	- ...
	- 32 : 31 mA
*/
CTR_6002DR2_API void LMLL_TxRfSetICT_TXDRV(int index)
{
	getMainModule()->getTxRf()->setICT_TXDRV(index);
}

/**
	@ingroup TxRF
	@brief Returns the bias current of the PAs.
	@retval 0 : 0 mA
	@retval 1 : 1 mA
	@retval ...
	@retval 12 : PAs take 12mA for each cell (default)
	@retval ...
	@retval 32 : 31 mA
*/
CTR_6002DR2_API int LMLL_TxRfGetICT_TXDRV()
{
	return  getMainModule()->getTxRf()->getICT_TXDRV();
}

/**
	@ingroup TxRF
	@brief Sets power down for TXLOBUF
	@param state stateDesc
	- 0 : powered up (default)
	- 1 : powered down
*/
CTR_6002DR2_API void LMLL_TxRfSetPD_TXLOBUF(bool state)
{
	getMainModule()->getTxRf()->setPD_TXLOBUF(state);
}

/**
	@ingroup TxRF
	@brief Returns state of power down for TXLOBUF
	@retval 0 : powered up (default)
	@retval 1 : powered down
*/
CTR_6002DR2_API bool LMLL_TxRfGetPD_TXLOBUF()
{
	return  getMainModule()->getTxRf()->getPD_TXLOBUF();
}

/**
	@ingroup TxRF
	@brief Sets Power down for PAs and AUXPA.
	@param state stateDesc
	- 0 : PA1, PA2 and AUXPA can be separately controlled (default)
	- 1 : PA1, PA2 and AUXPA all disabled
*/
CTR_6002DR2_API void LMLL_TxRfSetPD_TXDRV(bool state)
{
	getMainModule()->getTxRf()->setPD_TXDRV(state);
}

/**
	@ingroup TxRF
	@brief Returns state of Power down for PAs and AUXPA.
	@retval 0 : PA1, PA2 and AUXPA can be separately controlled (default)
	@retval 1 : PA1, PA2 and AUXPA all disabled
*/
CTR_6002DR2_API bool LMLL_TxRfGetPD_TXDRV()
{
	return  getMainModule()->getTxRf()->getPD_TXDRV();
}


// ============================================================================
// End of TxRf Module

// TxPLL Module
// ============================================================================
/**
	@ingroup TxPLL
	@brief Returns VCO cap log size.
	@return vco cap log length in bytes
*/
CTR_6002DR2_API unsigned int LMLL_TxPLLGetVcoCapLogLength()
{
	return getMainModule()->getTxPLL()->dlgVcoCapLog->Length();
}

/**
	@ingroup TxPLL
	@brief Copies main message log to supplied buffer
	@param buffer pointer to array, array must be big enough to fix all data, required size can be obtained from LMLL_TxPLLGetVcoCapLogLength()
*/
CTR_6002DR2_API void LMLL_TxPLLGetVcoCapLogMessages(char *buffer)
{
	getMainModule()->getTxPLL()->dlgVcoCapLog->Dump(buffer);
}

/**
	@ingroup TxPLL
	@brief Returns address of TxPLL module.
	@return TxPLL module address
*/
CTR_6002DR2_API char LMLL_TxPLLGetAddr()
{
	return  getMainModule()->getTxPLL()->getAddr();
}

/**
	@ingroup TxPLL
	@brief Sets TxPLL reference clock.
	@param RefClk reference clock in Hz
*/
CTR_6002DR2_API void LMLL_TxPLLSetRefClk(double RefClk)
{
	getMainModule()->getTxPLL()->SetRefClk(RefClk);
}

/**
	@ingroup TxPLL
	@brief Returns V tune state
	@retval 0 : VTUNE_H = 0 , VTUNE_L = 0
	@retval 1 : VTUNE_H = 0 , VTUNE_L = 1
	@retval 2 : VTUNE_H = 1 , VTUNE_L = 0
	@retval 3 : VTUNE_H = 1 , VTUNE_L = 1 (error)
*/
CTR_6002DR2_API int LMLL_TxPLLGetVTuneState()
{
	return  getMainModule()->getTxPLL()->GetVTuneState();
}

/**
	@ingroup TxPLL
	@brief Returns TxPLL reference clock
	@return reference clock in Hz
*/
CTR_6002DR2_API double LMLL_TxPLLGetRefClk()
{
	return  getMainModule()->getTxPLL()->GetRefClk();
}

/* not used in TxPLL
CTR_6002DR2_API void LMLL_TxPLL_SetActiveLOBuff(int ind)
{
	getMainModule()->getTxPLL()->CustSet_ActiveLOBuff(ind);
}
*/

/**
	@ingroup Application_Level_functions
	@brief Sets TxPLL frequency, calculates PLL data and performs tuning.
*/
CTR_6002DR2_API void LMAL_TxPLL_SetFrequency(double FreqGHz)
{
	getMainModule()->getTxPLL()->CustSet_LoadFrequency(FreqGHz);
}

/**
	@ingroup Application_Level_functions
	@brief Enables or disables TxPLL modules
	@param on power on state
*/
CTR_6002DR2_API void LMAL_TxPLL_PowerOn(bool on)
{
	getMainModule()->getTxPLL()->PLLPowerOn(on);
}

/**
	@ingroup TxPLL
	@brief Returns BIST state.
	@return BIST state
	- 0 : BIST is not running
	- 1 : BIST in progress
*/
CTR_6002DR2_API bool LMLL_TxPLLBIST_GetState()
{
	return  getMainModule()->getTxPLL()->BIST_GetState();
}

/**
	@ingroup TxPLL
	@brief Returns BIST signature.
	@return BIST signature
*/
CTR_6002DR2_API unsigned int LMLL_TxPLLBIST_GetSignature()
{
	return  getMainModule()->getTxPLL()->BIST_GetSignature();
}

/**
	@ingroup TxPLL
	@brief Start BIST procedure.
*/
CTR_6002DR2_API void LMLL_TxPLLBIST_Start()
{
	getMainModule()->getTxPLL()->BIST_Start();
}

/**
	@ingroup TxPLL
	@brief Returns TxPLL frequency.
	@return TxPLL frequency in MHz
*/
CTR_6002DR2_API double LMLL_TxPLLGetFrequency()
{
	return  getMainModule()->getTxPLL()->getFrequency();
}

/**
	@ingroup TxPLL

*/
CTR_6002DR2_API void LMLL_TxPLLChooseVcoCap()
{
	getMainModule()->getTxPLL()->btnChooseVcoCapClick();
}

/**
	@ingroup TxPLL
	@brief Sets dithering control.
	@param index value index from the list
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API void LMLL_TxPLLSetDITHEN(int index)
{
	getMainModule()->getTxPLL()->setDITHEN(index);
}

/**
	@ingroup TxPLL
	@brief Returns state of dithering control.
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API int LMLL_TxPLLGetDITHEN()
{
	return  getMainModule()->getTxPLL()->getDITHEN();
}

/**
	@ingroup TxPLL
	@brief Sets how many bits to dither if DITHEN=1.
	@param index value index from the list
	- 0 : 1 bit (default)
	- 1 : 2 bits
	- 2 : 3 bits
	- ...
	- 7 : 8 bits
*/
CTR_6002DR2_API void LMLL_TxPLLSetDITHN(int index)
{
	getMainModule()->getTxPLL()->setDITHN(index);
}

/**
	@ingroup TxPLL
	@brief Returns how many bits are dithered.
	@retval 0 : 1 bit
	@retval 1 : 2 bits
	@retval 2 : 3 bits
	@retval ...
	@retval 7 : 8 bits
*/
CTR_6002DR2_API int LMLL_TxPLLGetDITHN()
{
	return  getMainModule()->getTxPLL()->getDITHN();
}

/**
	@ingroup TxPLL
	@brief Enables or disables TxPLL modules.
	@param enabled is TxPLL enabled
*/
CTR_6002DR2_API void LMLL_TxPLLSetPwrPllMods(bool enabled)
{
	getMainModule()->getTxPLL()->setPwrPllMods(enabled);
}

/**
	@ingroup TxPLL
	@brief Returns whether TxPLL is enabled or disabled.
	@return is TxPLL enabled
*/
CTR_6002DR2_API bool LMLL_TxPLLGetPwrPllMods()
{
	return  getMainModule()->getTxPLL()->getPwrPllMods();
}

/**
	@ingroup TxPLL
	@brief Sets TxPLL decode mode
	@param index decode mode
	- 0 : decode power down/enable signals (default)
	- 1 : use power down/enable signals from test mode registers
*/
CTR_6002DR2_API void LMLL_TxPLLSetDecode(int index)
{
	getMainModule()->getTxPLL()->setDecode(index);
}

/**
	@ingroup TxPLL
	@brief Returns TxPLL decode mode.
	@retval 0 : decode power down/enable signals (default)
	@retval 1 : use power down/enable signals from test mode registers
*/
CTR_6002DR2_API int LMLL_TxPLLGetDecode()
{
	return  getMainModule()->getTxPLL()->getDecode();
}

/**
	@ingroup TxPLL
	@brief Sets TxPLL divider control
	@param index pll divider control
	- 0 : use delta sigma path (default)
	- 1 : bypass delta sigma, use BCODE and ACODE from test mode table
*/
CTR_6002DR2_API void LMLL_TxPLLSetMODE(int index)
{
	getMainModule()->getTxPLL()->setMODE(index);
}

/**
	@ingroup TxPLL
	@brief Returns TxPLL divider control
	@retval 0 : use delta sigma path (default)
	@retval 1 : bypass delta sigma, use BCODE and ACODE from test mode table
*/
CTR_6002DR2_API int LMLL_TxPLLGetMODE()
{
	return  getMainModule()->getTxPLL()->getMODE();
}

/**
	@ingroup TxPLL
	@brief Sets VCO selection
	@param index value index from the list
	- 0 : All VCOs powered down
	- 1 : Low frequency VCO (vco4)
	- 2 : Mid low frequency VCO (vco3) (default)
	- 3 : Mid high frequency VCO (vco2)
	- 4 : High frequency VCO (vco1)
*/
CTR_6002DR2_API void LMLL_TxPLLSetSELVCO(int index)
{
	getMainModule()->getTxPLL()->setSELVCO(index);
}

/**
	@ingroup TxPLL
	@brief Returns VCO selection
	@retval 0 : All VCOs powered down
	@retval 1 : Low frequency VCO (vco4)
	@retval 2 : Mid low frequency VCO (vco3)
	@retval 3 : Mid high frequency VCO (vco2)
	@retval 4 : High frequency VCO (vco1)
*/
CTR_6002DR2_API int LMLL_TxPLLGetSELVCO()
{
	return  getMainModule()->getTxPLL()->getSELVCO();
}

/**
	@ingroup TxPLL
	@brief Sets PLL output frequency range selection
	@param index value index from the list
	- 0 : All dividers powered down
	- 1 : Fvco/2 (2-4GHz range) (default)
	- 2 : Fvco/4 (1-2GHz range)
	- 3 : Fvco/8 (0.5-1GHz range)
	- 4 : Fvco/16 (0.25-0.5GHz range)
*/
CTR_6002DR2_API void LMLL_TxPLLSetFRANGE(int index)
{
	getMainModule()->getTxPLL()->setFRANGE(index);
}

/**
	@ingroup TxPLL
	@brief Returns PLL output frequency range selection
	@retval 0 : All dividers powered down
	@retval 1 : Fvco/2 (2-4GHz range) (default)
	@retval 2 : Fvco/4 (1-2GHz range)
	@retval 3 : Fvco/8 (0.5-1GHz range)
	@retval 4 : Fvco/16 (0.25-0.5GHz range)
*/
CTR_6002DR2_API int LMLL_TxPLLGetFRANGE()
{
	return  getMainModule()->getTxPLL()->getFRANGE();
}

/* not used in TXPLL
CTR_6002DR2_API void LMLL_TxPLLSetSELOUT(int index)
{
	getMainModule()->getTxPLL()->setSELOUT(index);
}

CTR_6002DR2_API int LMLL_TxPLLGetSELOUT()
{
	return  getMainModule()->getTxPLL()->getSELOUT();
}

*/

/**
	@ingroup TxPLL
	@brief Sets charge pump current.
	@param index value index from the list
	- 0 : 0 uA
	- 1 : 100 uA
	- 2 : 200 uA
	- ...
	- 12 : 1200 uA (default)
	- ...
	- 24 : 2400 uA
	- ... : 2400 uA
*/
CTR_6002DR2_API void LMLL_TxPLLSetICHP(int index)
{
	getMainModule()->getTxPLL()->setICHP(index);
}

/**
	@ingroup TxPLL
	@brief Returns charge pump current.
	@retval 0 : 0 uA
	@retval 1 : 100 uA
	@retval 2 : 200 uA
	@retval ...
	@retval 12 : 1200 uA
	@retval ...
	@retval 24 : 2400 uA
*/
CTR_6002DR2_API int LMLL_TxPLLGetICHP()
{
	return  getMainModule()->getTxPLL()->getICHP();
}

/**
	@ingroup TxPLL
	@brief Sets charge pump UP offset current.
	@param index value index from the list
	- 0 : 0 uA
	- 1 : 10 uA
	- ...
	- 24 : 240 uA
	- .. : 240 uA
*/
CTR_6002DR2_API void LMLL_TxPLLSetOFFUP(int index)
{
	getMainModule()->getTxPLL()->setOFFUP(index);
}

/**
	@ingroup TxPLL
  	@brief Returns charge pump UP offset current.
	@retval 0 : 0 uA
	@retval 1 : 10 uA
	@retval ...
	@retval 24 : 240 uA
*/
CTR_6002DR2_API int LMLL_TxPLLGetOFFUP()
{
	return  getMainModule()->getTxPLL()->getOFFUP();
}

/**
	@ingroup TxPLL
	@brief Sets charge pump DOWN offset current.
	@param index value index from the list
	- 0 : 0 uA
	- 1 : 10 uA
	- ...
	- 24 : 240 uA
	- .. : 240 uA
*/
CTR_6002DR2_API void LMLL_TxPLLSetOFFDOWN(int index)
{
	getMainModule()->getTxPLL()->setOFFDOWN(index);
}
/**
	@ingroup TxPLL
  	@brief Returns charge pump DOWN offset current.
	@retval 0 : 0 uA
	@retval 1 : 10 uA
	@retval ...
	@retval 24 : 240 uA
*/
CTR_6002DR2_API int LMLL_TxPLLGetOFFDOWN()
{
	return  getMainModule()->getTxPLL()->getOFFDOWN();
}

/**
	@ingroup TxPLL
	@brief Switch capacitance programming.
	@param index value index from the list
	- 0 : max capacitance, min frequency
	- ...
	- 63 : min capacitance, max frequency
*/
CTR_6002DR2_API void LMLL_TxPLLSetVCOCAP(int index)
{
	getMainModule()->getTxPLL()->setVCOCAP(index);
}

/**
	@ingroup TxPLL
	@brief Returns capacitance programming.
	@retval 0 : max capacitance, min frequency
	@retval ...
   	@retval 63 : min capacitance, max frequency
*/
CTR_6002DR2_API int LMLL_TxPLLGetVCOCAP()
{
	return  getMainModule()->getTxPLL()->getVCOCAP();
}

/**
	@ingroup TxPLL
	@brief Sets B counter control code.
	@param code control code
	- 0 : 7
	- 1 : 8
	- ...
	- 28 : 35
*/
CTR_6002DR2_API void LMLL_TxPLLSetBCODE(int code)
{
	getMainModule()->getTxPLL()->setBCODE(code);
}

/**
	@ingroup TxPLL
	@brief Returns B counter control code.
	@return control code
	@retval 0 : 7
	@retval 1 : 8
	@retval ...
	@retval 28 : 35
*/
CTR_6002DR2_API int LMLL_TxPLLGetBCODE()
{
	return  getMainModule()->getTxPLL()->getBCODE();
}

/**
	@ingroup TxPLL
	@brief Sets A counter control code.
	@param index control code
	- 0 : 0
	- 1 : 1
	- ...
	- 7 : 7
*/
CTR_6002DR2_API void LMLL_TxPLLSetACODE(int index)
{
	getMainModule()->getTxPLL()->setACODE(index);
}

/**
	@ingroup TxPLL
	@brief Returns A counter control code.
	@retval 0 : 0
	@retval 1 : 1
	@retval ...
	@retval 7 : 7
*/
CTR_6002DR2_API int LMLL_TxPLLGetACODE()
{
	return  getMainModule()->getTxPLL()->getACODE();
}

/**
	@ingroup TxPLL
	@brief Enables or disables LO buffer.
	@param enabled LO buffer enabled
*/

CTR_6002DR2_API void LMLL_TxPLLSetENLOBUF(bool enabled)
{
	getMainModule()->getTxPLL()->setENLOBUF(enabled);
}

/**
	@ingroup TxPLL
	@brief Returns whether LO buffer is enabled or disabled.
	@retval 0 : disabled (powered down)
	@retval 1 : enabled (powered up)
*/
CTR_6002DR2_API bool LMLL_TxPLLGetENLOBUF()
{
	return  getMainModule()->getTxPLL()->getENLOBUF();
}

/**
	@ingroup TxPLL
	@brief Enables or disables input limiter amplifier.
	@param enabled input limiter amplifier enabled
*/
CTR_6002DR2_API void LMLL_TxPLLSetENLAMP(bool enabled)
{
	getMainModule()->getTxPLL()->setENLAMP(enabled);
}

/**
	@ingroup TxPLL
	@brief Returns state of input limiter amplifier.
	@retval 0 - disabled (powered down)
	@retval 1 - enabled (powered up)
*/
CTR_6002DR2_API bool LMLL_TxPLLGetENLAMP()
{
	return  getMainModule()->getTxPLL()->getENLAMP();
}

/**
	@ingroup TxPLL
	@brief Sets PFD and charge pump power down.
	@param poweredUp power state
	- 1 PFD/CP powered up
	- 0 PFD/CP powered down
*/
CTR_6002DR2_API void LMLL_TxPLLSetPFDPD(bool poweredUp)
{
	getMainModule()->getTxPLL()->setPFDPD(poweredUp);
}

/**
	@ingroup TxPLL
	@brief Returns PFD and charge pump power down state.
	@retval 1 PFD/CP powered up
	@retval 0 PFD/CP powered down
*/
CTR_6002DR2_API bool LMLL_TxPLLGetPFDPD()
{
	return  getMainModule()->getTxPLL()->getPFDPD();
}

/**
	@ingroup TxPLL
	@brief Enables or disables feedback divider.
	@param enabled feedback divider enabled.
	- 0 : disabled (powered down)
	- 1 : enabled (powered up)
*/
CTR_6002DR2_API void LMLL_TxPLLSetENFEEDDIV(bool enabled)
{
	getMainModule()->getTxPLL()->setENFEEDDIV(enabled);
}

/**
	@ingroup TxPLL
	@brief Return whether feedback divider is enabled or disabled.
	@retval 0 : disabled (powered down)
	@retval 1 : enabled (powered up)
*/
CTR_6002DR2_API bool LMLL_TxPLLGetENFEEDDIV()
{
	return  getMainModule()->getTxPLL()->getENFEEDDIV();
}

/**
	@ingroup TxPLL
	@brief Sets VCO Comparator enable.
	@param enabled VCO comparator enabled
	- 0 : disabled ( powered down)
	- 1 : enabled ( powered up)
*/
CTR_6002DR2_API void LMLL_TxPLLSetPD_VCOCOMP_SX(bool enabled)
{
	getMainModule()->getTxPLL()->setPD_VCOCOMP_SX(enabled);
}

/**
	@ingroup TxPLL
	@brief Returns whether VCO Comparator is enabled or disabled.
	@retval 0 : disabled ( powered down)
	@retval 1 : enabled ( powered up)
*/
CTR_6002DR2_API bool LMLL_TxPLLGetPD_VCOCOMP_SX()
{
	return  getMainModule()->getTxPLL()->getPD_VCOCOMP_SX();
}

/**
	@ingroup TxPLL
	@brief Enables or disables output buffer.
	@param enabled output buffer enabled
	- 0 : Test signal output buffer disabled (default)
	- 1 : Test signal output buffer enabled
*/
CTR_6002DR2_API void LMLL_TxPLLSetOEN_TSTD_SX(bool enabled)
{
	getMainModule()->getTxPLL()->setOEN_TSTD_SX(enabled);
}

/**
	@ingroup TxPLL
	@brief Returns whether output buffer is enabled of disabled.
	@retval 0 : Test signal output buffer disabled (default)
	@retval 1 : Test signal output buffer enabled
*/
CTR_6002DR2_API bool LMLL_TxPLLGetOEN_TSTD_SX()
{
	return  getMainModule()->getTxPLL()->getOEN_TSTD_SX();
}

/**
	@ingroup TxPLL
	@brief Sets test signal pass enabled or disabled.
	@param enabled Test signal pass enabled
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API void LMLL_TxPLLSetPASSEN_TSTOD_SD(bool enabled)
{
	getMainModule()->getTxPLL()->setPASSEN_TSTOD_SD(enabled);
}

/**
	@ingroup TxPLL
	@brief Returns whether test signal pass enabled or disabled.
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_TxPLLGetPASSEN_TSTOD_SD()
{
	return  getMainModule()->getTxPLL()->getPASSEN_TSTOD_SD();
}

/**
	@ingroup TxPLL
	@brief Performs TxPLL tuning operations.
*/
CTR_6002DR2_API void LMLL_TxPLLTune()
{
	getMainModule()->getTxPLL()->Tune();
}

/**
	@ingroup TxPLL
	@brief Change PFD clock polarity.
	@param state clock state
	- 0 : PFD and DSM clocks in phase
	- 1 : PFD and DSM clocks inverted
*/
CTR_6002DR2_API void LMLL_TxPLLSetPFDCLKP(bool state)
{
	getMainModule()->getTxPLL()->setPFDCLKP(state);
}

/**
	@ingroup TxPLL
	@brief Returns PFD clock polarity.
	@retval 0 : PFD and DSM clocks in phase
   	@retval 1 : PFD and DSM clocks inverted
*/
CTR_6002DR2_API bool LMLL_TxPLLGetPFDCLKP()
{
	return  getMainModule()->getTxPLL()->getPFDCLKP();
}

/**
	@ingroup TxPLL
	@brief Set charge pump output state control
	@param state pump output state
	- 0 : Charge pump outputs in normal mode (default)
	- 1 : Charge pump outputs in tri-state (high impedance) mode
*/
CTR_6002DR2_API void LMLL_TxPLLSetTRI(bool state)
{
	getMainModule()->getTxPLL()->setTRI(state);
}

/**
	@ingroup TxPLL
	@brief Returns charge pump output control state
	@retval 0 : Charge pump outputs in normal mode (default)
	@retval 1 : Charge pump outputs in tri-state (high impedance) mode
*/
CTR_6002DR2_API bool LMLL_TxPLLGetTRI()
{
	return  getMainModule()->getTxPLL()->getTRI();
}

/**
	@ingroup TxPLL
	@brief Set charge pump output polarity mode.
	@param mode charge pump output mode
	- 0 : Normal mode
	- 1 : Charge pump output inverted
*/
CTR_6002DR2_API void LMLL_TxPLLSetPOL(bool mode)
{
	getMainModule()->getTxPLL()->setPOL(mode);
}

/**
	@ingroup TxPLL
	@brief Returns charge pump output polarity mode.
	@retval 0 : Normal mode
	@retval 1 : Charge pump output inverted
*/
CTR_6002DR2_API bool LMLL_TxPLLGetPOL()
{
	return  getMainModule()->getTxPLL()->getPOL();
}

/**
	@ingroup TxPLL
	@brief Sets delta sigma auto bypass when NFRAC = 0
	@param enabled delta sigma auto bypass enabled
*/
CTR_6002DR2_API void LMLL_TxPLLSetAUTOBYP(bool enabled)
{
	getMainModule()->getTxPLL()->setAUTOBYP(enabled);
}

/**
	@ingroup TxPLL
	@brief Returns whether delta sigma auto bypass is enabled or disabled
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_TxPLLGetAUTOBYP()
{
	return  getMainModule()->getTxPLL()->getAUTOBYP();
}

/**
	@ingroup TxPLL
	@brief Enables or disables PFD UP pulses.
	@param enabled PFD UP pulses enabled
*/
CTR_6002DR2_API void LMLL_TxPLLSetEN_PFD_UP(bool enabled)
{
	getMainModule()->getTxPLL()->setEN_PFD_UP(enabled);
}

/**
	@ingroup TxPLL
	@brief Returns whether PFD UP pulses are enabled or disabled.
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_TxPLLGetEN_PFD_UP()
{
	return  getMainModule()->getTxPLL()->getEN_PFD_UP();
}

/**
	@ingroup TxPLL
	@brief Sets Bypass of VCO regulator.
	@param state bypass state
	- 0 : not bypassed
	- 1 : regulator bypassed
*/
CTR_6002DR2_API void LMLL_TxPLLSetBYPVCOREG(bool state)
{
	getMainModule()->getTxPLL()->setBYPVCOREG(state);
}

/**
	@ingroup TxPLL
	@brief Returns bypass of VCO regulator.
	@retval 0 : not bypassed
	@retval 1 : regulator bypassed
*/
CTR_6002DR2_API bool LMLL_TxPLLGetBYPVCOREG()
{
	return  getMainModule()->getTxPLL()->getBYPVCOREG();
}

/**
	@ingroup TxPLL
	@brief Sets VCO regulator power down.
	@param state regulator state
	- 0 : regulator powered up
	- 1 : regulator powered down
*/
CTR_6002DR2_API void LMLL_TxPLLSetPDVCOREG(bool state)
{
	getMainModule()->getTxPLL()->setPDVCOREG(state);
}

/**
	@ingroup TxPLL
	@brief Returns VCO regulator power down.
	@retval 0 : regulator powered up
	@retval 1 : regulator powered down
*/
CTR_6002DR2_API bool LMLL_TxPLLGetPDVCOREG()
{
	return  getMainModule()->getTxPLL()->getPDVCOREG();
}

/**
	@ingroup TxPLL
	@brief Sets VCO regulator band gap settling time control.

	VCO regulator band gap settling time control. Shorts the resistor in
	band gap to speed up charging for faster response.
	After the initial charge up, it should be disabled.
	@param state
	- 0 : switch open
	- 1 : resistor shorted
*/
CTR_6002DR2_API void LMLL_TxPLLSetFSTVCOBG(bool state)
{
	getMainModule()->getTxPLL()->setFSTVCOBG(state);
}

/**
	@ingroup TxPLL
	@brief Returns VCO regulator band gap settling time control.
	@retval 0 : switch open
	@retval 1 : resistor shorted
*/
CTR_6002DR2_API bool LMLL_TxPLLGetFSTVCOBG()
{
	return  getMainModule()->getTxPLL()->getFSTVCOBG();
}

/**
	@ingroup TxPLL
	@brief Sets VCO regulator output voltage control
	@param index value index from the list
	- 0 : 1.4V, min output
	- 1 : 1.5V
	- 2 : 1.6V
	- ...
	- 5 : 1.9V (default)
	- ...
	- 12 : 2.6V, max output
*/
CTR_6002DR2_API void LMLL_TxPLLSetVOVCOREG(int index)
{
	getMainModule()->getTxPLL()->setVOVCOREG(index);
}

/**
	@ingroup TxPLL
	@brief Returns VCO regulator output voltage control
	@retval 0 : 1.4V, min output
	@retval 1 : 1.5V
	@retval 2 : 1.6V
	@retval ...
	@retval 12 : 2.6V, max output
*/
CTR_6002DR2_API int LMLL_TxPLLGetVOVCOREG()
{
	return  getMainModule()->getTxPLL()->getVOVCOREG();
}

/**
	@ingroup TxPLL
	@brief Sets delta sigma/BIST clock select
	@param index value index from the list
	- 0 : clock disabled
	- 1 : use reference clock for BIST
	- 2 : use feedback divider output, normal operation and BIST
	- 3 : clock disabled
*/

CTR_6002DR2_API void LMLL_TxPLLSetBCLKSEL(int index)
{
	getMainModule()->getTxPLL()->setBCLKSEL(index);
}

/**
	@ingroup TxPLL
	@brief Returns delta sigma/BIST clock select
	@retval 0 : clock disabled
	@retval 1 : use reference clock for BIST
	@retval 2 : use feedback divider output, normal operation and BIST
	@retval 3 : clock disabled
*/
CTR_6002DR2_API int LMLL_TxPLLGetBCLKSEL()
{
	return  getMainModule()->getTxPLL()->getBCLKSEL();
}

/**
	@ingroup TxPLL
	@brief Sets delta sigma/BIST input select
	@param index value index from the list
	- 0 : NINT/NFRAC registers, normal operation (default)
	- 1 : Pseudo random sequence select
*/
CTR_6002DR2_API void LMLL_TxPLLSetBINSEL(int index)
{
	getMainModule()->getTxPLL()->setBINSEL(index);
}

/**
	@ingroup TxPLL
	@brief Returns delta sigma/BIST input select
	@retval 0 : NINT/NFRAC registers, normal operation (default)
	@retval 1 : Pseudo random sequence select
*/
CTR_6002DR2_API int LMLL_TxPLLGetBINSEL()
{
	return  getMainModule()->getTxPLL()->getBINSEL();
}

/**
	@ingroup TxPLL
	@brief Returns calculated values for integer mode
	@param &divN Divider N
	@param &Fvco Fvco Ghz
	@param &Fvco2 Fvco/2 Ghz
	@param &Fvco4 Fvco/4 Ghz
	@param &Fvco8 Fvco/8 Ghz
	@param &Fvco16 Fvco/16 Ghz
*/
CTR_6002DR2_API void LMLL_TxPLLGetValuesForIntegerMode(int &divN, double &Fvco, double &Fvco2, double &Fvco4, double &Fvco8, double &Fvco16)
{
	divN = getMainModule()->getTxPLL()->lblN_info;
	Fvco = getMainModule()->getTxPLL()->lblFvcoInt_info;
	Fvco2 = getMainModule()->getTxPLL()->lblFvco2Int_info;
	Fvco4 = getMainModule()->getTxPLL()->lblFvco4Int_info;
	Fvco8 = getMainModule()->getTxPLL()->lblFvco8Int_info;
	Fvco16 = getMainModule()->getTxPLL()->lblFvco16Int_info;
}

/**
	@ingroup TxPLL
	@brief Returns calculated values for fractional mode.
	@param &nInt N integer
	@param &nFrac N fractional
	@param &div divider
	@param &ROutF Real output frequency GHz
	@param &VcoF VCO frequency GHz
*/
CTR_6002DR2_API void LMLL_TxPLLGetValuesForFractionalMode(int &nInt, int &nFrac, double &div, double &ROutF, double &VcoF)
{
	nInt = getMainModule()->getTxPLL()->lblNint_info;
	nFrac = getMainModule()->getTxPLL()->lblNfrac_info;
	div = getMainModule()->getTxPLL()->lblDiv_info;
	ROutF = getMainModule()->getTxPLL()->lblROutF_info;
	VcoF = getMainModule()->getTxPLL()->lblVcoF_info;
}
// ============================================================================
// End of TxPLL

// RxPLL Module
// ============================================================================
/**
	@ingroup RxPLL
	@brief Returns VCO cap log size.
	@return vco cap log length in bytes
*/
CTR_6002DR2_API unsigned int LMLL_RxPLLGetVcoCapLogLength()
{
	return getMainModule()->getRxPLL()->dlgVcoCapLog->Length();
}

/**
	@ingroup RxPLL
	@brief Copies main message log to supplied buffer
	@param buffer pointer to array, array must be big enough to fix all data, required size can be obtained from LMLL_RxPLLGetVcoCapLogLength()
*/
CTR_6002DR2_API void LMLL_RxPLLGetVcoCapLogMessages(char *buffer)
{
	getMainModule()->getRxPLL()->dlgVcoCapLog->Dump(buffer);
}

/**
	@ingroup RxPLL
	@brief Returns address of RxPLL module.
	@return RxPLL module address
*/
CTR_6002DR2_API char LMLL_RxPLLGetAddr()
{
	return  getMainModule()->getRxPLL()->getAddr();
}

/**
	@ingroup RxPLL
	@brief Sets RxPLL reference clock.
	@param RefClk reference clock in Hz
*/
CTR_6002DR2_API void LMLL_RxPLLSetRefClk(double RefClk)
{
	getMainModule()->getRxPLL()->SetRefClk(RefClk);
}

/**
	@ingroup RxPLL
	@brief Returns V tune state
	@retval 0 : VTUNE_H = 0 , VTUNE_L = 0
	@retval 1 : VTUNE_H = 0 , VTUNE_L = 1
	@retval 2 : VTUNE_H = 1 , VTUNE_L = 0
	@retval 3 : VTUNE_H = 1 , VTUNE_L = 1 (error)
*/
CTR_6002DR2_API int LMLL_RxPLLGetVTuneState()
{
	return  getMainModule()->getRxPLL()->GetVTuneState();
}

/**
	@ingroup RxPLL
	@brief Returns RxPLL reference clock
	@return reference clock in Hz
*/
CTR_6002DR2_API double LMLL_RxPLLGetRefClk()
{
	return  getMainModule()->getRxPLL()->GetRefClk();
}

/*
CTR_6002DR2_API void LMLL_RxPLL_SetActiveLOBuff(int ind)
{
	getMainModule()->getRxPLL()->CustSet_ActiveLOBuff(ind);
}
*/

/**
	@ingroup Application_Level_functions
	@brief Sets RxPLL frequency, calculates PLL data and performs tuning.
*/
CTR_6002DR2_API void LMAL_RxPLL_SetFrequency(double FreqGHz)
{
	getMainModule()->getRxPLL()->CustSet_LoadFrequency(FreqGHz);
}

/**
	@ingroup Application_Level_functions
	@brief Enables or disables RxPLL modules
	@param on power on state
*/
CTR_6002DR2_API void LMAL_RxPLL_PowerOn(bool on)
{
	getMainModule()->getRxPLL()->PLLPowerOn(on);
}

/**
	@ingroup RxPLL
	@brief Returns BIST state.
	@return BIST state
	- 0 : BIST is not running
	- 1 : BIST in progress
*/
CTR_6002DR2_API bool LMLL_RxPLLBIST_GetState()
{
	return  getMainModule()->getRxPLL()->BIST_GetState();
}

/**
	@ingroup RxPLL
	@brief Returns BIST signature.
	@return BIST signature
*/
CTR_6002DR2_API unsigned int LMLL_RxPLLBIST_GetSignature()
{
	return  getMainModule()->getRxPLL()->BIST_GetSignature();
}

/**
	@ingroup RxPLL
	@brief Start BIST procedure.
*/
CTR_6002DR2_API void LMLL_RxPLLBIST_Start()
{
	getMainModule()->getRxPLL()->BIST_Start();
}

/**
	@ingroup RxPLL
	@brief Returns RxPLL frequency.
	@return RxPLL frequency in MHz
*/
CTR_6002DR2_API double LMLL_RxPLLGetFrequency()
{
	return  getMainModule()->getRxPLL()->getFrequency();
}

/**
	@ingroup RxPLL
*/
CTR_6002DR2_API void LMLL_RxPLLChooseVcoCap()
{
	getMainModule()->getRxPLL()->btnChooseVcoCapClick();
}

/**
	@ingroup RxPLL
	@brief Sets dithering control.
	@param index value index from the list
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API void LMLL_RxPLLSetDITHEN(int index)
{
	getMainModule()->getRxPLL()->setDITHEN(index);
}

/**
	@ingroup RxPLL
	@brief Returns state of dithering control.
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API int LMLL_RxPLLGetDITHEN()
{
	return  getMainModule()->getRxPLL()->getDITHEN();
}

/**
	@ingroup RxPLL
	@brief Sets how many bits to dither if DITHEN=1.
	@param index value index from the list
	- 0 : 1 bit (default)
	- 1 : 2 bits
	- 2 : 3 bits
	- ...
	- 7 : 8 bits
*/
CTR_6002DR2_API void LMLL_RxPLLSetDITHN(int index)
{
	getMainModule()->getRxPLL()->setDITHN(index);
}

/**
	@ingroup RxPLL
	@brief Returns how many bits are dithered.
	@retval 0 : 1 bit
	@retval 1 : 2 bits
	@retval 2 : 3 bits
	@retval ...
	@retval 7 : 8 bits
*/
CTR_6002DR2_API int LMLL_RxPLLGetDITHN()
{
	return  getMainModule()->getRxPLL()->getDITHN();
}

/**
	@ingroup RxPLL
	@brief Enables or disables RxPLL modules.
	@param enabled is RxPLL enabled
*/
CTR_6002DR2_API void LMLL_RxPLLSetPwrPllMods(bool enabled)
{
	getMainModule()->getRxPLL()->setPwrPllMods(enabled);
}

/**
	@ingroup RxPLL
	@brief Returns whether RxPLL is enabled or disabled.
	@return is RxPLL enabled
*/
CTR_6002DR2_API bool LMLL_RxPLLGetPwrPllMods()
{
	return  getMainModule()->getRxPLL()->getPwrPllMods();
}

/**
	@ingroup RxPLL
	@brief Sets RxPLL decode mode
	@param index decode mode
	- 0 : decode power down/enable signals (default)
	- 1 : use power down/enable signals from test mode registers
*/
CTR_6002DR2_API void LMLL_RxPLLSetDecode(int index)
{
	getMainModule()->getRxPLL()->setDecode(index);
}

/**
	@ingroup RxPLL
	@brief Returns RxPLL decode mode.
	@retval 0 : decode power down/enable signals (default)
	@retval 1 : use power down/enable signals from test mode registers
*/
CTR_6002DR2_API int LMLL_RxPLLGetDecode()
{
	return  getMainModule()->getRxPLL()->getDecode();
}

/**
	@ingroup RxPLL
	@brief Sets RxPLL divider control
	@param index pll divider control
	- 0 : use delta sigma path (default)
	- 1 : bypass delta sigma, use BCODE and ACODE from test mode table
*/
CTR_6002DR2_API void LMLL_RxPLLSetMODE(int index)
{
	getMainModule()->getRxPLL()->setMODE(index);
}

/**
	@ingroup RxPLL
	@brief Returns RxPLL divider control
	@retval 0 : use delta sigma path (default)
	@retval 1 : bypass delta sigma, use BCODE and ACODE from test mode table
*/
CTR_6002DR2_API int LMLL_RxPLLGetMODE()
{
	return  getMainModule()->getRxPLL()->getMODE();
}

/**
	@ingroup RxPLL
	@brief Sets VCO selection
	@param index value index from the list
	- 0 : All VCOs powered down
	- 1 : Low frequency VCO (vco4)
	- 2 : Mid low frequency VCO (vco3) (default)
	- 3 : Mid high frequency VCO (vco2)
	- 4 : High frequency VCO (vco1)
*/
CTR_6002DR2_API void LMLL_RxPLLSetSELVCO(int index)
{
	getMainModule()->getRxPLL()->setSELVCO(index);
}

/**
	@ingroup RxPLL
	@brief Returns VCO selection
	@retval 0 : All VCOs powered down
	@retval 1 : Low frequency VCO (vco4)
	@retval 2 : Mid low frequency VCO (vco3)
	@retval 3 : Mid high frequency VCO (vco2)
	@retval 4 : High frequency VCO (vco1)
*/
CTR_6002DR2_API int LMLL_RxPLLGetSELVCO()
{
	return  getMainModule()->getRxPLL()->getSELVCO();
}

/**
	@ingroup RxPLL
	@brief Sets PLL output frequency range selection
	@param index value index from the list
	- 0 : All dividers powered down
	- 1 : Fvco/2 (2-4GHz range) (default)
	- 2 : Fvco/4 (1-2GHz range)
	- 3 : Fvco/8 (0.5-1GHz range)
	- 4 : Fvco/16 (0.25-0.5GHz range)
*/
CTR_6002DR2_API void LMLL_RxPLLSetFRANGE(int index)
{
	getMainModule()->getRxPLL()->setFRANGE(index);
}

/**
	@ingroup RxPLL
	@brief Returns PLL output frequency range selection
	@retval 0 : All dividers powered down
	@retval 1 : Fvco/2 (2-4GHz range) (default)
	@retval 2 : Fvco/4 (1-2GHz range)
	@retval 3 : Fvco/8 (0.5-1GHz range)
	@retval 4 : Fvco/16 (0.25-0.5GHz range)
*/
CTR_6002DR2_API int LMLL_RxPLLGetFRANGE()
{
	return  getMainModule()->getRxPLL()->getFRANGE();
}

/**
	@ingroup RxPLL
	@brief Sets output buffer in RX PLL.
	@param index value index from the list
	- 0 : All output buffers powered down
	- 1 : First buffer enabled for LNA1 path (default)
	- 2 : Second buffer enabled for LNA2 path
	- 3 : Third buffer enabled for LNA3 path
*/
CTR_6002DR2_API void LMLL_RxPLLSetSELOUT(int index)
{
	getMainModule()->getRxPLL()->setSELOUT(index);
}

/**
	@ingroup RxPLL
	@brief Returns output buffer in RX PLL.
	@retval 0 : All output buffers powered down
	@retval 1 : First buffer enabled for LNA1 path (default)
	@retval 2 : Second buffer enabled for LNA2 path
	@retval 3 : Third buffer enabled for LNA3 path
*/
CTR_6002DR2_API int LMLL_RxPLLGetSELOUT()
{
	return  getMainModule()->getRxPLL()->getSELOUT();
}

/**
	@ingroup RxPLL
	@brief Sets charge pump current.
	@param index value index from the list
	- 0 : 0 uA
	- 1 : 100 uA
	- 2 : 200 uA
	- ...
	- 12 : 1200 uA (default)
	- ...
	- 24 : 2400 uA
	- ... : 2400 uA
*/
CTR_6002DR2_API void LMLL_RxPLLSetICHP(int index)
{
	getMainModule()->getRxPLL()->setICHP(index);
}

/**
	@ingroup RxPLL
	@brief Returns charge pump current.
	@retval 0 : 0 uA
	@retval 1 : 100 uA
	@retval 2 : 200 uA
	@retval ...
	@retval 12 : 1200 uA
	@retval ...
	@retval 24 : 2400 uA
*/
CTR_6002DR2_API int LMLL_RxPLLGetICHP()
{
	return  getMainModule()->getRxPLL()->getICHP();
}

/**
	@ingroup RxPLL
	@brief Sets charge pump UP offset current.
	@param index value index from the list
	- 0 : 0 uA
	- 1 : 10 uA
	- ...
	- 24 : 240 uA
	- .. : 240 uA
*/
CTR_6002DR2_API void LMLL_RxPLLSetOFFUP(int index)
{
	getMainModule()->getRxPLL()->setOFFUP(index);
}

/**
	@ingroup RxPLL
  	@brief Returns charge pump UP offset current.
	@retval 0 : 0 uA
	@retval 1 : 10 uA
	@retval ...
	@retval 24 : 240 uA
*/
CTR_6002DR2_API int LMLL_RxPLLGetOFFUP()
{
	return  getMainModule()->getRxPLL()->getOFFUP();
}

/**
	@ingroup RxPLL
	@brief Sets charge pump DOWN offset current.
	@param index value index from the list
	- 0 : 0 uA
	- 1 : 10 uA
	- ...
	- 24 : 240 uA
	- .. : 240 uA
*/
CTR_6002DR2_API void LMLL_RxPLLSetOFFDOWN(int index)
{
	getMainModule()->getRxPLL()->setOFFDOWN(index);
}
/**
	@ingroup RxPLL
  	@brief Returns charge pump DOWN offset current.
	@retval 0 : 0 uA
	@retval 1 : 10 uA
	@retval ...
	@retval 24 : 240 uA
*/
CTR_6002DR2_API int LMLL_RxPLLGetOFFDOWN()
{
	return  getMainModule()->getRxPLL()->getOFFDOWN();
}

/**
	@ingroup RxPLL
	@brief Switch capacitance programming.
	@param index value index from the list
	- 0 : max capacitance, min frequency
	- ...
	- 63 : min capacitance, max frequency
*/
CTR_6002DR2_API void LMLL_RxPLLSetVCOCAP(int index)
{
	getMainModule()->getRxPLL()->setVCOCAP(index);
}

/**
	@ingroup RxPLL
	@brief Returns capacitance programming.
	@retval 0 : max capacitance, min frequency
	@retval ...
   	@retval 63 : min capacitance, max frequency
*/
CTR_6002DR2_API int LMLL_RxPLLGetVCOCAP()
{
	return  getMainModule()->getRxPLL()->getVCOCAP();
}

/**
	@ingroup RxPLL
	@brief Sets B counter control code.
	@param code control code
	- 0 : 7
	- 1 : 8
	- ...
	- 28 : 35
*/
CTR_6002DR2_API void LMLL_RxPLLSetBCODE(int code)
{
	getMainModule()->getRxPLL()->setBCODE(code);
}

/**
	@ingroup RxPLL
	@brief Returns B counter control code.
	@return control code
	@retval 0 : 7
	@retval 1 : 8
	@retval ...
	@retval 28 : 35
*/
CTR_6002DR2_API int LMLL_RxPLLGetBCODE()
{
	return  getMainModule()->getRxPLL()->getBCODE();
}

/**
	@ingroup RxPLL
	@brief Sets A counter control code.
	@param index control code
	- 0 : 0
	- 1 : 1
	- ...
	- 7 : 7
*/
CTR_6002DR2_API void LMLL_RxPLLSetACODE(int index)
{
	getMainModule()->getRxPLL()->setACODE(index);
}

/**
	@ingroup RxPLL
	@brief Returns A counter control code.
	@retval 0 : 0
	@retval 1 : 1
	@retval ...
	@retval 7 : 7
*/
CTR_6002DR2_API int LMLL_RxPLLGetACODE()
{
	return  getMainModule()->getRxPLL()->getACODE();
}

/**
	@ingroup RxPLL
	@brief Enables or disables LO buffer.
	@param enabled LO buffer enabled
*/

CTR_6002DR2_API void LMLL_RxPLLSetENLOBUF(bool enabled)
{
	getMainModule()->getRxPLL()->setENLOBUF(enabled);
}

/**
	@ingroup RxPLL
	@brief Returns whether LO buffer is enabled or disabled.
	@retval 0 : disabled (powered down)
	@retval 1 : enabled (powered up)
*/
CTR_6002DR2_API bool LMLL_RxPLLGetENLOBUF()
{
	return  getMainModule()->getRxPLL()->getENLOBUF();
}

/**
	@ingroup RxPLL
	@brief Enables or disables input limiter amplifier.
	@param enabled input limiter amplifier enabled
*/
CTR_6002DR2_API void LMLL_RxPLLSetENLAMP(bool enabled)
{
	getMainModule()->getRxPLL()->setENLAMP(enabled);
}

/**
	@ingroup RxPLL
	@brief Returns state of input limiter amplifier.
	@retval 0 - disabled (powered down)
	@retval 1 - enabled (powered up)
*/
CTR_6002DR2_API bool LMLL_RxPLLGetENLAMP()
{
	return  getMainModule()->getRxPLL()->getENLAMP();
}

/**
	@ingroup RxPLL
	@brief Sets PFD and charge pump power down.
	@param poweredUp power state
	- 1 PFD/CP powered up
	- 0 PFD/CP powered down
*/
CTR_6002DR2_API void LMLL_RxPLLSetPFDPD(bool poweredUp)
{
	getMainModule()->getRxPLL()->setPFDPD(poweredUp);
}

/**
	@ingroup RxPLL
	@brief Returns PFD and charge pump power down state.
	@retval 1 PFD/CP powered up
	@retval 0 PFD/CP powered down
*/
CTR_6002DR2_API bool LMLL_RxPLLGetPFDPD()
{
	return  getMainModule()->getRxPLL()->getPFDPD();
}

/**
	@ingroup RxPLL
	@brief Enables or disables feedback divider.
	@param enabled feedback divider enabled.
	- 0 : disabled (powered down)
	- 1 : enabled (powered up)
*/
CTR_6002DR2_API void LMLL_RxPLLSetENFEEDDIV(bool enabled)
{
	getMainModule()->getRxPLL()->setENFEEDDIV(enabled);
}

/**
	@ingroup RxPLL
	@brief Return whether feedback divider is enabled or disabled.
	@retval 0 : disabled (powered down)
	@retval 1 : enabled (powered up)
*/
CTR_6002DR2_API bool LMLL_RxPLLGetENFEEDDIV()
{
	return  getMainModule()->getRxPLL()->getENFEEDDIV();
}

/**
	@ingroup RxPLL
	@brief Sets VCO Comparator enable.
	@param enabled VCO comparator enabled
	- 0 : disabled ( powered down)
	- 1 : enabled ( powered up)
*/
CTR_6002DR2_API void LMLL_RxPLLSetPD_VCOCOMP_SX(bool enabled)
{
	getMainModule()->getRxPLL()->setPD_VCOCOMP_SX(enabled);
}

/**
	@ingroup RxPLL
	@brief Returns whether VCO Comparator is enabled or disabled.
	@retval 0 : disabled ( powered down)
	@retval 1 : enabled ( powered up)
*/
CTR_6002DR2_API bool LMLL_RxPLLGetPD_VCOCOMP_SX()
{
	return  getMainModule()->getRxPLL()->getPD_VCOCOMP_SX();
}

/**
	@ingroup RxPLL
	@brief Enables or disables output buffer.
	@param enabled output buffer enabled
	- 0 : Test signal output buffer disabled (default)
	- 1 : Test signal output buffer enabled
*/
CTR_6002DR2_API void LMLL_RxPLLSetOEN_TSTD_SX(bool enabled)
{
	getMainModule()->getRxPLL()->setOEN_TSTD_SX(enabled);
}

/**
	@ingroup RxPLL
	@brief Returns whether output buffer is enabled of disabled.
	@retval 0 : Test signal output buffer disabled (default)
	@retval 1 : Test signal output buffer enabled
*/
CTR_6002DR2_API bool LMLL_RxPLLGetOEN_TSTD_SX()
{
	return  getMainModule()->getRxPLL()->getOEN_TSTD_SX();
}

/**
	@ingroup RxPLL
	@brief Sets test signal pass enabled or disabled.
	@param enabled Test signal pass enabled
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API void LMLL_RxPLLSetPASSEN_TSTOD_SD(bool enabled)
{
	getMainModule()->getRxPLL()->setPASSEN_TSTOD_SD(enabled);
}

/**
	@ingroup RxPLL
	@brief Returns whether test signal pass enabled or disabled.
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_RxPLLGetPASSEN_TSTOD_SD()
{
	return  getMainModule()->getRxPLL()->getPASSEN_TSTOD_SD();
}

/**
	@ingroup RxPLL
	@brief Performs RxPLL tuning operations.
*/
CTR_6002DR2_API void LMLL_RxPLLTune()
{
	getMainModule()->getRxPLL()->Tune();
}

/**
	@ingroup RxPLL
	@brief Change PFD clock polarity.
	@param state clock state
	- 0 : PFD and DSM clocks in phase
	- 1 : PFD and DSM clocks inverted
*/
CTR_6002DR2_API void LMLL_RxPLLSetPFDCLKP(bool state)
{
	getMainModule()->getRxPLL()->setPFDCLKP(state);
}

/**
	@ingroup RxPLL
	@brief Returns PFD clock polarity.
	@retval 0 : PFD and DSM clocks in phase
   	@retval 1 : PFD and DSM clocks inverted
*/
CTR_6002DR2_API bool LMLL_RxPLLGetPFDCLKP()
{
	return  getMainModule()->getRxPLL()->getPFDCLKP();
}

/**
	@ingroup RxPLL
	@brief Set charge pump output state control
	@param state pump output state
	- 0 : Charge pump outputs in normal mode (default)
	- 1 : Charge pump outputs in tri-state (high impedance) mode
*/
CTR_6002DR2_API void LMLL_RxPLLSetTRI(bool state)
{
	getMainModule()->getRxPLL()->setTRI(state);
}

/**
	@ingroup RxPLL
	@brief Returns charge pump output control state
	@retval 0 : Charge pump outputs in normal mode (default)
	@retval 1 : Charge pump outputs in tri-state (high impedance) mode
*/
CTR_6002DR2_API bool LMLL_RxPLLGetTRI()
{
	return  getMainModule()->getRxPLL()->getTRI();
}

/**
	@ingroup RxPLL
	@brief Set charge pump output polarity mode.
	@param mode charge pump output mode
	- 0 : Normal mode
	- 1 : Charge pump output inverted
*/
CTR_6002DR2_API void LMLL_RxPLLSetPOL(bool mode)
{
	getMainModule()->getRxPLL()->setPOL(mode);
}

/**
	@ingroup RxPLL
	@brief Returns charge pump output polarity mode.
	@retval 0 : Normal mode
	@retval 1 : Charge pump output inverted
*/
CTR_6002DR2_API bool LMLL_RxPLLGetPOL()
{
	return  getMainModule()->getRxPLL()->getPOL();
}

/**
	@ingroup RxPLL
	@brief Sets delta sigma auto bypass when NFRAC = 0
	@param enabled delta sigma auto bypass enabled
*/
CTR_6002DR2_API void LMLL_RxPLLSetAUTOBYP(bool enabled)
{
	getMainModule()->getRxPLL()->setAUTOBYP(enabled);
}

/**
	@ingroup RxPLL
	@brief Returns whether delta sigma auto bypass is enabled or disabled
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_RxPLLGetAUTOBYP()
{
	return  getMainModule()->getRxPLL()->getAUTOBYP();
}

/**
	@ingroup RxPLL
	@brief Enables or disables PFD UP pulses.
	@param enabled PFD UP pulses enabled
*/
CTR_6002DR2_API void LMLL_RxPLLSetEN_PFD_UP(bool enabled)
{
	getMainModule()->getRxPLL()->setEN_PFD_UP(enabled);
}

/**
	@ingroup RxPLL
	@brief Returns whether PFD UP pulses are enabled or disabled.
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_RxPLLGetEN_PFD_UP()
{
	return  getMainModule()->getRxPLL()->getEN_PFD_UP();
}

/**
	@ingroup RxPLL
	@brief Sets Bypass of VCO regulator.
	@param state bypass state
	- 0 : not bypassed
	- 1 : regulator bypassed
*/
CTR_6002DR2_API void LMLL_RxPLLSetBYPVCOREG(bool state)
{
	getMainModule()->getRxPLL()->setBYPVCOREG(state);
}

/**
	@ingroup RxPLL
	@brief Returns bypass of VCO regulator.
	@retval 0 : not bypassed
	@retval 1 : regulator bypassed
*/
CTR_6002DR2_API bool LMLL_RxPLLGetBYPVCOREG()
{
	return  getMainModule()->getRxPLL()->getBYPVCOREG();
}

/**
	@ingroup RxPLL
	@brief Sets VCO regulator power down.
	@param state regulator state
	- 0 : regulator powered up
	- 1 : regulator powered down
*/
CTR_6002DR2_API void LMLL_RxPLLSetPDVCOREG(bool state)
{
	getMainModule()->getRxPLL()->setPDVCOREG(state);
}

/**
	@ingroup RxPLL
	@brief Returns VCO regulator power down.
	@retval 0 : regulator powered up
	@retval 1 : regulator powered down
*/
CTR_6002DR2_API bool LMLL_RxPLLGetPDVCOREG()
{
	return  getMainModule()->getRxPLL()->getPDVCOREG();
}

/**
	@ingroup RxPLL
	@brief Sets VCO regulator band gap settling time control.

	VCO regulator band gap settling time control. Shorts the resistor in
	band gap to speed up charging for faster response.
	After the initial charge up, it should be disabled.
	@param state
	- 0 : switch open
	- 1 : resistor shorted
*/
CTR_6002DR2_API void LMLL_RxPLLSetFSTVCOBG(bool state)
{
	getMainModule()->getRxPLL()->setFSTVCOBG(state);
}

/**
	@ingroup RxPLL
	@brief Returns VCO regulator band gap settling time control.
	@retval 0 : switch open
	@retval 1 : resistor shorted
*/
CTR_6002DR2_API bool LMLL_RxPLLGetFSTVCOBG()
{
	return  getMainModule()->getRxPLL()->getFSTVCOBG();
}

/**
	@ingroup RxPLL
	@brief Sets VCO regulator output voltage control
	@param index value index from the list
	- 0 : 1.4V, min output
	- 1 : 1.5V
	- 2 : 1.6V
	- ...
	- 5 : 1.9V (default)
	- ...
	- 12 : 2.6V, max output
*/
CTR_6002DR2_API void LMLL_RxPLLSetVOVCOREG(int index)
{
	getMainModule()->getRxPLL()->setVOVCOREG(index);
}

/**
	@ingroup RxPLL
	@brief Returns VCO regulator output voltage control
	@retval 0 : 1.4V, min output
	@retval 1 : 1.5V
	@retval 2 : 1.6V
	@retval ...
	@retval 12 : 2.6V, max output
*/
CTR_6002DR2_API int LMLL_RxPLLGetVOVCOREG()
{
	return  getMainModule()->getRxPLL()->getVOVCOREG();
}

/**
	@ingroup RxPLL
	@brief Sets delta sigma/BIST clock select
	@param index value index from the list
	- 0 : clock disabled
	- 1 : use reference clock for BIST
	- 2 : use feedback divider output, normal operation and BIST
	- 3 : clock disabled
*/

CTR_6002DR2_API void LMLL_RxPLLSetBCLKSEL(int index)
{
	getMainModule()->getRxPLL()->setBCLKSEL(index);
}

/**
	@ingroup RxPLL
	@brief Returns delta sigma/BIST clock select
	@retval 0 : clock disabled
	@retval 1 : use reference clock for BIST
	@retval 2 : use feedback divider output, normal operation and BIST
	@retval 3 : clock disabled
*/
CTR_6002DR2_API int LMLL_RxPLLGetBCLKSEL()
{
	return  getMainModule()->getRxPLL()->getBCLKSEL();
}

/**
	@ingroup RxPLL
	@brief Sets delta sigma/BIST input select
	@param index value index from the list
	- 0 : NINT/NFRAC registers, normal operation (default)
	- 1 : Pseudo random sequence select
*/
CTR_6002DR2_API void LMLL_RxPLLSetBINSEL(int index)
{
	getMainModule()->getRxPLL()->setBINSEL(index);
}

/**
	@ingroup RxPLL
	@brief Returns delta sigma/BIST input select
	@retval 0 : NINT/NFRAC registers, normal operation (default)
	@retval 1 : Pseudo random sequence select
*/
CTR_6002DR2_API int LMLL_RxPLLGetBINSEL()
{
	return  getMainModule()->getRxPLL()->getBINSEL();
}

/**
	@ingroup RxPLL
	@brief Returns calculated values for integer mode
	@param &divN Divider N
	@param &Fvco Fvco Ghz
	@param &Fvco2 Fvco/2 Ghz
	@param &Fvco4 Fvco/4 Ghz
	@param &Fvco8 Fvco/8 Ghz
	@param &Fvco16 Fvco/16 Ghz
*/
CTR_6002DR2_API void LMLL_RxPLLGetValuesForIntegerMode(int &divN, double &Fvco, double &Fvco2, double &Fvco4, double &Fvco8, double &Fvco16)
{
	divN = getMainModule()->getRxPLL()->lblN_info;
	Fvco = getMainModule()->getRxPLL()->lblFvcoInt_info;
	Fvco2 = getMainModule()->getRxPLL()->lblFvco2Int_info;
	Fvco4 = getMainModule()->getRxPLL()->lblFvco4Int_info;
	Fvco8 = getMainModule()->getRxPLL()->lblFvco8Int_info;
	Fvco16 = getMainModule()->getRxPLL()->lblFvco16Int_info;
}

/**
	@ingroup RxPLL
	@brief Returns calculated values for fractional mode.
	@param &nInt N integer
	@param &nFrac N fractional
	@param &div divider
	@param &ROutF Real output frequency GHz
	@param &VcoF VCO frequency GHz
*/
CTR_6002DR2_API void LMLL_RxPLLGetValuesForFractionalMode(int &nInt, int &nFrac, double &div, double &ROutF, double &VcoF)
{
	nInt = getMainModule()->getRxPLL()->lblNint_info;
	nFrac = getMainModule()->getRxPLL()->lblNfrac_info;
	div = getMainModule()->getRxPLL()->lblDiv_info;
	ROutF = getMainModule()->getRxPLL()->lblROutF_info;
	VcoF = getMainModule()->getRxPLL()->lblVcoF_info;
}
// ============================================================================
// End of RxPLL

//  TxLPF Module
//==============================================================================
/**
	@ingroup TxLPF
	@brief Returns TxLPF module address.
	@return TxLPF module address
*/
CTR_6002DR2_API char LMLL_TxLPFGetAddr()
{
	return  getMainModule()->getTxLpf()->getAddr();
}

/**
	@ingroup TxLPF
	@brief resets all DC Calibration modules
*/
CTR_6002DR2_API void LMLL_TxLPFDCResetCalibration()
{
	getMainModule()->getTxLpf()->DCResetCalibration();
}

/**
	@ingroup TxLPF
	@brief Loads value to module selected by LMLL_TxLPFSetDCCalAddr()
	@param value value to load
*/
CTR_6002DR2_API void LMLL_TxLPFDCLoadValues(unsigned int value)
{

	getMainModule()->getTxLpf()->DCLoadValues(value);
}

/**
	@ingroup TxLPF
	@brief Start calibration on module, selected by LMLL_TxLPFSetDCCalAddr()
*/
CTR_6002DR2_API void LMLL_TxLPFDCStartCalibration()
{
	getMainModule()->getTxLpf()->DCStartCalibration();
}

/**
	@ingroup TxLPF
	@brief Reads and returns DC calibration values from the chip.
	@param &calibVal calibration value
	@param &lockPattern lock pattern
	@param &calibStatus calibration status
	@param &compValue comparator value
*/
CTR_6002DR2_API void LMLL_TxLPFDCReadValues(int &calibVal, int &lockPattern, int &calibStatus, int &compValue)
{
	getMainModule()->getTxLpf()->DCGetCalibrationData(calibVal, lockPattern, calibStatus, compValue);
}

/*
CTR_6002DR2_API int LMLL_TxLPFGetCalVal()
{
	return  getMainModule()->getTxLpf()->GetCalVal();
}
*/

/*
CTR_6002DR2_API void LMLL_TxLPF_BypassLpfOn()
{
	getMainModule()->getTxLpf()->CustSet_BypassLpfON();
}

CTR_6002DR2_API void LMLL_TxLPF_BypassLpfOff()
{
	getMainModule()->getTxLpf()->CustSet_BypassLpfOFF();
}
*/

/**
	@ingroup TxLPF
	@brief Enables or disables TxLPF modules.
	@param on power on state
*/
CTR_6002DR2_API void LMAL_TxLPF_PowerOn(bool on)
{
	getMainModule()->getTxLpf()->LpfPowerOn(on);
}

/*
CTR_6002DR2_API void LMLL_TxLPF_EnableDCOffsetCompOnly()
{
	getMainModule()->getTxLpf()->CustSet_EnableDCOffsetCompOnly();
}

CTR_6002DR2_API void LMLL_TxLPF_RestoreDCOffsetCompOnly()
{
	getMainModule()->getTxLpf()->CustSet_RestoreDCOffsetCompOnly();
}
*/

/*
CTR_6002DR2_API void LMLL_TxLPF_BypassLPFOnlyOn()
{
	getMainModule()->getTxLpf()->CustSet_BypassLPFOnlyOn();
}

CTR_6002DR2_API void LMLL_TxLPF_BypassLPFOnlyOff()
{
	getMainModule()->getTxLpf()->CustSet_BypassLPFOnlyOff();
}
*/

/**
	@ingroup TxLPF
	@brief Sets TxLPF decode mode
	@param index value index from the list
	- 0 : decode control signals (default)
	- 1 : use control signals from test mode registers
*/
CTR_6002DR2_API void LMLL_TxLPFSetDecode(int index)
{
	getMainModule()->getTxLpf()->setDecode(index);
}

/**
	@ingroup TxLPF
	@brief Returns TxLPF decode mode
	@retval 0 : decode control signals (default)
	@retval 1 : use control signals from test mode registers
*/
CTR_6002DR2_API int LMLL_TxLPFGetDecode()
{
	return  getMainModule()->getTxLpf()->getDecode();
}

/**
	@ingroup TxLPF
	@brief Sets LPF bandwidth
	@param index value index from the list
	- 0 : 14 MHz
	- 1 : 10 MHz
	- 2 : 7 MHz
	- 3 : 6 MHz
	- 4 : 5 MHz
	- 5 : 4.375 MHz
	- 6 : 3.5 MHz
	- 7 : 3 MHz
	- 8 : 2.75 MHz
	- 9 : 2.5 MHz
	- 10 :  1.92 MHz
	- 11 : 1.5 MHz
	- 12 : 1.375 MHz
	- 13 : 1.25 MHz
	- 14 : 0.875 MHz
	- 15 : 0.75 MHz
*/
CTR_6002DR2_API void LMLL_TxLPFSetLpfBw(int index)
{
	getMainModule()->getTxLpf()->setLpfBw(index);
}

/**
	@ingroup TxLPF
	@brief Returns LPF bandwidth
	@retval 0 : 14 MHz
	@retval 1 : 10 MHz
	@retval 2 : 7 MHz
	@retval 3 : 6 MHz
	@retval 4 : 5 MHz
	@retval 5 : 4.375 MHz
	@retval 6 : 3.5 MHz
	@retval 7 : 3 MHz
	@retval 8 : 2.75 MHz
	@retval 9 : 2.5 MHz
	@retval 10 :  1.92 MHz
	@retval 11 : 1.5 MHz
	@retval 12 : 1.375 MHz
	@retval 13 : 1.25 MHz
	@retval 14 : 0.875 MHz
	@retval 15 : 0.75 MHz
*/
CTR_6002DR2_API int LMLL_TxLPFGetLpfBw()
{
	return  getMainModule()->getTxLpf()->getLpfBw();
}

/**
	@ingroup TxLPF
	@brief Sets resistor calibration control for the DC offset cancellation DAC.
	@param index resistor calibration control, values from 0 to 63
*/
CTR_6002DR2_API void LMLL_TxLPFSetDCOffset(int index)
{
	getMainModule()->getTxLpf()->setDCOffset(index);
}

/**
	@ingroup TxLPF
	@brief Returns resistor calibration control for the DC offset cancellation DAC.
	@return resistor calibration control
*/
CTR_6002DR2_API int LMLL_TxLPFGetDCOffset()
{
	return  getMainModule()->getTxLpf()->getDCOffset();
}

/**
	@ingroup TxLPF
	@brief Sets calibration value, coming from TRX_LPF_CAL module.
	@param value calibration value [0 - 7]
*/
CTR_6002DR2_API void LMLL_TxLPFSetRcCal(int value)
{
	getMainModule()->getTxLpf()->setRcCal(value);
}

/**
	@ingroup TxLPF
	@brief Returns calibration value, coming from TRX_LPF_CAL module.
	@return calibration value
*/
CTR_6002DR2_API int LMLL_TxLPFGetRcCal()
{
	return  getMainModule()->getTxLpf()->getRcCal();
}

/**
	@ingroup TxLPF
	@brief Enables or disables TxLPF
	@param state TxLPF enabled
*/
CTR_6002DR2_API void LMLL_TxLPFSetPwrLpf(bool state)
{
	getMainModule()->getTxLpf()->setPwrLpf(state);
}

/**
	@ingroup TxLPF
	@brief Returns whether TxLPF is enabled or disabled
	@return is TxLPF enabled
*/
CTR_6002DR2_API bool LMLL_TxLPFGetPwrLpf()
{
	return  getMainModule()->getTxLpf()->getPwrLpf();
}

/**
	@ingroup TxLPF
	@brief Sets power down for the DAC in the DC offset cancellation block.
	@param state DC offset DAC enabled
	- 0 : Powered down
	- 1 : Enabled
*/
CTR_6002DR2_API void LMLL_TxLPFSetPwrDCDac(bool state)
{
	getMainModule()->getTxLpf()->setPwrDCDac(state);
}

/**
	@ingroup TxLPF
	@brief Returns power down for the DAC in the DC offset cancellation block.
	@retval 0 : Powered down
    @retval 1 : Enabled
*/
CTR_6002DR2_API bool LMLL_TxLPFGetPwrDCDac()
{
	return  getMainModule()->getTxLpf()->getPwrDCDac();
}

/**
	@ingroup TxLPF
	@brief Sets power down signal for the dc_ref_con3 block.
	@param state
	- 0 : Powered down
	- 1 : Enabled
*/
CTR_6002DR2_API void LMLL_TxLPFSetPwrDCRef(bool state)
{
	getMainModule()->getTxLpf()->setPwrDCRef(state);
}

/**
	@ingroup TxLPF
	@brief Returns power down signal for the dc_ref_con3 block.
	@retval 0 : Powered down
	@retval 1 : Enabled
*/
CTR_6002DR2_API bool LMLL_TxLPFGetPwrDCRef()
{
	return  getMainModule()->getTxLpf()->getPwrDCRef();
}

/**
	@ingroup TxLPF
	@brief Sets power down for DC offset comparator in the DC offset cancellation block.
	@param state DC offset comparator enabled
	- 0 : powered down
	- 1 : enabled

	Should be powered up only when DC offset cancellation algorithm is running.
*/
CTR_6002DR2_API void LMLL_TxLPFSetPwrDCCmpr(bool state)
{
	getMainModule()->getTxLpf()->setPwrDCCmpr(state);
}

/**
	@ingroup TxLPF
	@brief Returns power down for DC offset comparator in the DC offset cancellation block.
	@return state DC offset comparator enabled
	- 0 : powered down
	- 1 : enabled
*/
CTR_6002DR2_API bool LMLL_TxLPFGetPwrDCCmpr()
{
	return  getMainModule()->getTxLpf()->getPwrDCCmpr();
}

/**
	@ingroup TxLPF
	@brief Sets active calibration module address.
	@param address calibration module address
	- 0 : I filter
	- 1 : Q filter
*/
CTR_6002DR2_API void LMLL_TxLPFSetDCCalAddr(int address)
{
	getMainModule()->getTxLpf()->setDCCalAddr(address);
}

/**
	@ingroup TxLPF
	@brief Returns active calibration module address.
	@retval 0 : I filter
	@retval 1 : Q filter
*/
CTR_6002DR2_API int LMLL_TxLPFGetDCCalAddr()
{
	return  getMainModule()->getTxLpf()->getDCCalAddr();
}

/*
	@ingroup TxLPF
	@brief Sets calibration value
	@param value calibration value

CTR_6002DR2_API void LMLL_TxLPFSetCalVal(int value)
{
	getMainModule()->getTxLpf()->setCalVal(value);
}
*/

/**
	@ingroup TxLPF
	@brief Enalbes or disables TxLPF modules.
	@param state TxLPF modules enabled
*/
CTR_6002DR2_API void LMLL_TxLPFSetPwrLpfMods(bool state)
{
	getMainModule()->getTxLpf()->setPwrLpfMods(state);
}

/**
	@ingroup TxLPF
	@brief Returns whether TxLPF modules are enabled or disabled.
	@return TxLPF modules enabled
*/
CTR_6002DR2_API bool LMLL_TxLPFGetPwrLpfMods()
{
	return  getMainModule()->getTxLpf()->getPwrLpfMods();
}

/**
	@ingroup TxLPF
	@brief Enables or disables LPF bypass
	@param state bypass state
	- 0 : normal operation
	- 1 : bypass switches will bypass the LPF
*/
CTR_6002DR2_API void LMLL_TxLPFSetLpfByp(int state)
{
	getMainModule()->getTxLpf()->setLpfByp(state);
}

/**
	@ingroup TxLPF
	@brief Returns whether LPF bypass is enabled or disabled
	@retval 0 : normal operation
	@retval 1 : bypass switches will bypass the LPF
*/
CTR_6002DR2_API int LMLL_TxLPFGetLpfByp()
{
	return  getMainModule()->getTxLpf()->getLpfByp();
}

/**
	@ingroup TxLPF
	@brief Sets TX data DAC buffers power down
	@param state buffers state
	- 0 : powered down
	- 1 : enabled (default)
*/
CTR_6002DR2_API void LMLL_TxLPFSetTX_DACBUF_EN(bool state)
{
	getMainModule()->getTxLpf()->setTX_DACBUF_EN(state);
}

/**
	@ingroup TxLPF
	@brief Returns TX data DAC buffers power down
	@retval 0 : powered down
	@retval 1 : enabled (default)
*/
CTR_6002DR2_API bool LMLL_TxLPFGetTX_DACBUF_EN()
{
	return  getMainModule()->getTxLpf()->getTX_DACBUF_EN();
}

/**
	@ingroup TxLPF
	@brief Returns DC calibration values
	@param &dcRegVal calibration value
	@param &lockPattern lock pattern
	@param &calibStatus calibration status
	@param &compValue comparator value
*/
CTR_6002DR2_API void LMLL_TxLPFGetDCCalibrationData(int &dcRegVal, int &lockPattern, int &calibStatus, int &compValue)
{
	getMainModule()->getTxLpf()->DCGetCalibrationData(dcRegVal, lockPattern, calibStatus, compValue);
/*
	dcRegVal = getMainModule()->getTxLpf()->lbDC_REGVAL;
	lockPattern = getMainModule()->getTxLpf()->lblDC_LOCK;
	calibStatus = getMainModule()->getTxLpf()->lblDC_CLBR_DONE;
	compValue = getMainModule()->getTxLpf()->lblDC_UD;
*/
}

//==============================================================================
// End of TxLPF

//  RxLPF Module
//==============================================================================
/**
	@ingroup RxLPF
	@brief Returns RxLPF module address.
	@return RxLPF module address
*/
CTR_6002DR2_API char LMLL_RxLPFGetAddr()
{
	return  getMainModule()->getRxLpf()->getAddr();
}

/**
	@ingroup RxLPF
	@brief resets all DC Calibration modules
*/
CTR_6002DR2_API void LMLL_RxLPFDCResetCalibration()
{
	getMainModule()->getRxLpf()->DCResetCalibration();
}

/**
	@ingroup RxLPF
	@brief Loads value to module selected by LMLL_RxLPFSetDCCalAddr()
	@param value value to load
*/
CTR_6002DR2_API void LMLL_RxLPFDCLoadValues(unsigned int value)
{
	getMainModule()->getRxLpf()->DCLoadValues(value);
}

/**
	@ingroup RxLPF
	@brief Start calibration on module, selected by LMLL_RxLPFSetDCCalAddr()
*/
CTR_6002DR2_API void LMLL_RxLPFDCStartCalibration()
{
	getMainModule()->getRxLpf()->DCStartCalibration();
}

/**
	@ingroup RxLPF
	@brief Reads and returns DC calibration values from the chip.
	@param &calibVal calibration value
	@param &lockPattern lock pattern
	@param &calibStatus calibration status
	@param &compValue comparator value
*/
CTR_6002DR2_API void LMLL_RxLPFDCReadValues(int &calibVal, int &lockPattern, int &calibStatus, int &compValue)
{
	getMainModule()->getRxLpf()->DCGetCalibrationData(calibVal, lockPattern, calibStatus, compValue);
}

/*
	@ingroup RxLPF
	@brief Returns DC Calibration value.

CTR_6002DR2_API int LMLL_RxLPFGetCalVal()
{
	return  getMainModule()->getRxLpf()->GetCalVal();
}
*/

/*
CTR_6002DR2_API void LMLL_RxLPF_BypassLpfOn()
{
	getMainModule()->getRxLpf()->CustSet_BypassLpfON();
}

CTR_6002DR2_API void LMLL_RxLPF_BypassLpfOff()
{
	getMainModule()->getRxLpf()->CustSet_BypassLpfOFF();
}
*/

/**
	@ingroup RxLPF
	@brief Enables or disables RxLPF modules.
	@param on power on state
*/
CTR_6002DR2_API void LMAL_RxLPF_PowerOn(bool on)
{
	getMainModule()->getRxLpf()->LpfPowerOn(on);
}

/*
CTR_6002DR2_API void LMLL_RxLPF_EnableDCOffsetCompOnly()
{
	getMainModule()->getRxLpf()->CustSet_EnableDCOffsetCompOnly();
}

CTR_6002DR2_API void LMLL_RxLPF_RestoreDCOffsetCompOnly()
{
	getMainModule()->getRxLpf()->CustSet_RestoreDCOffsetCompOnly();
}
*/

/*
CTR_6002DR2_API void LMLL_RxLPF_BypassLPFOnlyOn()
{
	getMainModule()->getRxLpf()->CustSet_BypassLPFOnlyOn();
}

CTR_6002DR2_API void LMLL_RxLPF_BypassLPFOnlyOff()
{
	getMainModule()->getRxLpf()->CustSet_BypassLPFOnlyOff();
}
*/

/**
	@ingroup RxLPF
	@brief Sets RxLPF decode mode
	@param index value index from the list
	- 0 : decode control signals (default)
	- 1 : use control signals from test mode registers
*/
CTR_6002DR2_API void LMLL_RxLPFSetDecode(int index)
{
	getMainModule()->getRxLpf()->setDecode(index);
}

/**
	@ingroup RxLPF
	@brief Returns RxLPF decode mode
	@retval 0 : decode control signals (default)
	@retval 1 : use control signals from test mode registers
*/
CTR_6002DR2_API int LMLL_RxLPFGetDecode()
{
	return  getMainModule()->getRxLpf()->getDecode();
}

/**
	@ingroup RxLPF
	@brief Sets LPF bandwidth
	@param index value index from the list
	- 0 : 14 MHz
	- 1 : 10 MHz
	- 2 : 7 MHz
	- 3 : 6 MHz
	- 4 : 5 MHz
	- 5 : 4.375 MHz
	- 6 : 3.5 MHz
	- 7 : 3 MHz
	- 8 : 2.75 MHz
	- 9 : 2.5 MHz
	- 10 :  1.92 MHz
	- 11 : 1.5 MHz
	- 12 : 1.375 MHz
	- 13 : 1.25 MHz
	- 14 : 0.875 MHz
	- 15 : 0.75 MHz
*/
CTR_6002DR2_API void LMLL_RxLPFSetLpfBw(int index)
{
	getMainModule()->getRxLpf()->setLpfBw(index);
}

/**
	@ingroup RxLPF
	@brief Returns LPF bandwidth
	@retval 0 : 14 MHz
	@retval 1 : 10 MHz
	@retval 2 : 7 MHz
	@retval 3 : 6 MHz
	@retval 4 : 5 MHz
	@retval 5 : 4.375 MHz
	@retval 6 : 3.5 MHz
	@retval 7 : 3 MHz
	@retval 8 : 2.75 MHz
	@retval 9 : 2.5 MHz
	@retval 10 :  1.92 MHz
	@retval 11 : 1.5 MHz
	@retval 12 : 1.375 MHz
	@retval 13 : 1.25 MHz
	@retval 14 : 0.875 MHz
	@retval 15 : 0.75 MHz
*/
CTR_6002DR2_API int LMLL_RxLPFGetLpfBw()
{
	return  getMainModule()->getRxLpf()->getLpfBw();
}

/**
	@ingroup RxLPF
	@brief Sets resistor calibration control for the DC offset cancellation DAC.
	@param index resistor calibration control, values from 0 to 63
*/
CTR_6002DR2_API void LMLL_RxLPFSetDCOffset(int index)
{
	getMainModule()->getRxLpf()->setDCOffset(index);
}

/**
	@ingroup RxLPF
	@brief Returns resistor calibration control for the DC offset cancellation DAC.
	@return resistor calibration control
*/
CTR_6002DR2_API int LMLL_RxLPFGetDCOffset()
{
	return  getMainModule()->getRxLpf()->getDCOffset();
}

/**
	@ingroup RxLPF
	@brief Sets calibration value, coming from TRX_LPF_CAL module.
	@param value calibration value [0 - 7]
*/
CTR_6002DR2_API void LMLL_RxLPFSetRcCal(int value)
{
	getMainModule()->getRxLpf()->setRcCal(value);
}

/**
	@ingroup RxLPF
	@brief Returns calibration value, coming from TRX_LPF_CAL module.
	@return calibration value
*/
CTR_6002DR2_API int LMLL_RxLPFGetRcCal()
{
	return  getMainModule()->getRxLpf()->getRcCal();
}

/**
	@ingroup RxLPF
	@brief Enables or disables RxLPF
	@param state RxLPF enabled
*/
CTR_6002DR2_API void LMLL_RxLPFSetPwrLpf(bool state)
{
	getMainModule()->getRxLpf()->setPwrLpf(state);
}

/**
	@ingroup RxLPF
	@brief Returns whether RxLPF is enabled or disabled
	@return is RxLPF enabled
*/
CTR_6002DR2_API bool LMLL_RxLPFGetPwrLpf()
{
	return  getMainModule()->getRxLpf()->getPwrLpf();
}

/**
	@ingroup RxLPF
	@brief Sets power down for the DAC in the DC offset cancellation block.
	@param state DC offset DAC enabled
	- 0 : Powered down
	- 1 : Enabled
*/
CTR_6002DR2_API void LMLL_RxLPFSetPwrDCDac(bool state)
{
	getMainModule()->getRxLpf()->setPwrDCDac(state);
}

/**
	@ingroup RxLPF
	@brief Returns power down for the DAC in the DC offset cancellation block.
	@retval 0 : Powered down
    @retval 1 : Enabled
*/
CTR_6002DR2_API bool LMLL_RxLPFGetPwrDCDac()
{
	return  getMainModule()->getRxLpf()->getPwrDCDac();
}

/**
	@ingroup RxLPF
	@brief Sets power down signal for the dc_ref_con3 block.
	@param state
	- 0 : Powered down
	- 1 : Enabled
*/
CTR_6002DR2_API void LMLL_RxLPFSetPwrDCRef(bool state)
{
	getMainModule()->getRxLpf()->setPwrDCRef(state);
}

/**
	@ingroup RxLPF
	@brief Returns power down signal for the dc_ref_con3 block.
	@retval 0 : Powered down
	@retval 1 : Enabled
*/
CTR_6002DR2_API bool LMLL_RxLPFGetPwrDCRef()
{
	return  getMainModule()->getRxLpf()->getPwrDCRef();
}

/**
	@ingroup RxLPF
	@brief Sets power down for DC offset comparator in the DC offset cancellation block.
	@param state DC offset comparator enabled
	- 0 : powered down
	- 1 : enabled

	Should be powered up only when DC offset cancellation algorithm is running.
*/
CTR_6002DR2_API void LMLL_RxLPFSetPwrDCCmpr(bool state)
{
	getMainModule()->getRxLpf()->setPwrDCCmpr(state);
}

/**
	@ingroup RxLPF
	@brief Returns power down for DC offset comparator in the DC offset cancellation block.
	@return state DC offset comparator enabled
	- 0 : powered down
	- 1 : enabled
*/
CTR_6002DR2_API bool LMLL_RxLPFGetPwrDCCmpr()
{
	return  getMainModule()->getRxLpf()->getPwrDCCmpr();
}

/**
	@ingroup RxLPF
	@brief Sets active calibration module address.
	@param address calibration module address
	- 0 : I filter
	- 1 : Q filter
*/
CTR_6002DR2_API void LMLL_RxLPFSetDCCalAddr(int address)
{
	getMainModule()->getRxLpf()->setDCCalAddr(address);
}

/**
	@ingroup RxLPF
	@brief Returns active calibration module address.
	@retval 0 : I filter
	@retval 1 : Q filter
*/
CTR_6002DR2_API int LMLL_RxLPFGetDCCalAddr()
{
	return  getMainModule()->getRxLpf()->getDCCalAddr();
}

/*
	@ingroup RxLPF
	@brief Sets calibration value
	@param value calibration value

CTR_6002DR2_API void LMLL_RxLPFSetCalVal(int value)
{
	getMainModule()->getRxLpf()->setCalVal(value);
}
*/

/**
	@ingroup RxLPF
	@brief Enalbes or disables RxLPF modules.
	@param state RxLPF modules enabled
*/
CTR_6002DR2_API void LMLL_RxLPFSetPwrLpfMods(bool state)
{
	getMainModule()->getRxLpf()->setPwrLpfMods(state);
}

/**
	@ingroup RxLPF
	@brief Returns whether RxLPF modules are enabled or disabled.
	@return RxLPF modules enabled
*/
CTR_6002DR2_API bool LMLL_RxLPFGetPwrLpfMods()
{
	return  getMainModule()->getRxLpf()->getPwrLpfMods();
}

/**
	@ingroup RxLPF
	@brief Enables or disables LPF bypass
	@param state bypass state
	- 0 : normal operation
	- 1 : bypass switches will bypass the LPF
*/
CTR_6002DR2_API void LMLL_RxLPFSetLpfByp(int state)
{
	getMainModule()->getRxLpf()->setLpfByp(state);
}

/**
	@ingroup RxLPF
	@brief Returns whether LPF bypass is enabled or disabled
	@retval 0 : normal operation
	@retval 1 : bypass switches will bypass the LPF
*/
CTR_6002DR2_API int LMLL_RxLPFGetLpfByp()
{
	return  getMainModule()->getRxLpf()->getLpfByp();
}

/**
	@ingroup RxLPF
	@brief Returns DC calibration values
	@param &dcRegVal calibration value
	@param &lockPattern lock pattern
	@param &calibStatus calibration status
	@param &compValue comparator value
*/
CTR_6002DR2_API void LMLL_RxLPFGetDCCalibrationData(int &dcRegVal, int &lockPattern, int &calibStatus, int &compValue)
{
	getMainModule()->getRxLpf()->DCGetCalibrationData(dcRegVal, lockPattern, calibStatus, compValue);
/*
	dcRegVal = getMainModule()->getRxLpf()->lbDC_REGVAL;
	lockPattern = getMainModule()->getRxLpf()->lblDC_LOCK;
	calibStatus = getMainModule()->getRxLpf()->lblDC_CLBR_DONE;
	compValue = getMainModule()->getRxLpf()->lblDC_UD;
*/
}

//==============================================================================
// End of RxLPF

// Top Module
//==============================================================================
/**
	@ingroup TopModule
	@brief Sets decode mode
	@param mode decode mode
	- 0 : decode control signals (default)
	- 1 : use control signals from test mode registers.
*/
CTR_6002DR2_API void LMLL_TopSetDecode(int mode)
{
	getMainModule()->getTop()->setDecode(mode);
}

/**
	@ingroup TopModule
	@brief Returns decode mode
	@retval 0 : decode control signals (default)
	@retval 1 : use control signals from test mode registers.
*/
CTR_6002DR2_API int LMLL_TopGetDecode()
{
	return  getMainModule()->getTop()->getDecode();
}

/**
	@ingroup TopModule
	@brief Sets SPI port mode
	@param mode SPI mode
	- 0 : 3 wire
	- 1 : 4 wire
*/
CTR_6002DR2_API void LMLL_TopSetSpiMode(int mode)
{
	getMainModule()->getTop()->setSpiMode(mode);
}

/**
	@ingroup TopModule
	@brief Returns SPI port mode
	@retval 0 : 3 wire
	@retval 1 : 4 wire
*/
CTR_6002DR2_API int LMLL_TopGetSpiMode()
{
	return  getMainModule()->getTop()->getSpiMode();
}

/**
	@ingroup TopModule
	@brief Sets DSM soft reset state
	@param state soft reset state
	- 0 : reset state
	- 1 : inactive
*/
CTR_6002DR2_API void LMLL_TopSetDsmRst(int state)
{
	getMainModule()->getTop()->setDsmRst(state);
}

/**
	@ingroup TopModule
	@brief Returns DSM soft reset state
	@retval 0 : reset state
	@retval 1 : inactive
*/
CTR_6002DR2_API int LMLL_TopGetDsmRst()
{
	return  getMainModule()->getTop()->getDsmRst();
}

/**
	@ingroup TopModule
	@brief Sets	RX baseband bypass.
	@param state RXTIA shorted to the output pins
	- 0 : disabled (default)
	- 1 : enabled (shorted)

	If = 1, RXTIA output is shorted to the output pins. If enabled, RXLPF and RXVGA2 should be disabled (powered down)
*/
CTR_6002DR2_API void LMLL_TopSetRxTestModeEn(bool state)
{
	getMainModule()->getTop()->setRxTestModeEn(state);
}

/**
	@ingroup TopModule
	@brief Returns RX baseband bypass.
	@return is RXTIA shorted to the output pins
	@retval 0 : disabled (default)
	@retval 1 : enabled (shorted)
*/
CTR_6002DR2_API bool LMLL_TopGetRxTestModeEn()
{
	return  getMainModule()->getTop()->getRxTestModeEn();
}

/**
	@ingroup TopModule
	@brief Sets SPI clock distribution.
	@param index spi clock index
	- 0 : Tx DSM SPI
	- 1 : Tx LPF SPI
	- 2 : Rx DSM SPI
	- 3 : Rx LPF SPI
	- 4 : Rx VGA2 DCCAL
	- 5 : LPF CAL
	- 6 : PLLCLKOUT
	@param enabled clock enabled

	Enables or disables SPI clock selected by index.
*/
CTR_6002DR2_API void LMLL_TopSetSpiClkBuf(int index, bool enabled)
{
	getMainModule()->getTop()->setSpiClkBuf(index, enabled);
}

/**
	@ingroup TopModule
	@brief Returns SPI clock state
	@param index spi clock index
	- 0 : Tx DSM SPI
	- 1 : Tx LPF SPI
	- 2 : Rx DSM SPI
	- 3 : Rx LPF SPI
	- 4 : Rx VGA2 DCCAL
	- 5 : LPF CAL
	- 6 : PLLCLKOUT
	@return clock enabled
*/
CTR_6002DR2_API bool LMLL_TopGetSpiClkBuf(int index)
{
	return  getMainModule()->getTop()->getSpiClkBuf(index);
}

/**
	@ingroup TopModule
	@brief Sets RF loopback control
	@param index loopback path
	- 0 : RF loopback disabled
	- 1 TXMIX output connected to LNA1 path
	- 2 TXMIX output connected to LNA2 path
	- 3 TXMIX output connected to LNA3 path

	When activated, LNAs should be disabled (powered down).
*/
CTR_6002DR2_API void LMLL_TopSetRFLB(int index)
{
	getMainModule()->getTop()->setRFLB(index);
}

/**
	@ingroup TopModule
	@brief Returns RF loopback control
	@retval 0 : RF loopback disabled
	@retval 1 TXMIX output connected to LNA1 path
	@retval 2 TXMIX output connected to LNA2 path
	@retval 3 TXMIX output connected to LNA3 path
*/
CTR_6002DR2_API int LMLL_TopGetRFLB()
{
	return  getMainModule()->getTop()->getRFLB();
}

/**
	@ingroup TopModule
	@brief Sets	reset signal used at the beginning of calibration cycle.
	@param state reset signal enabled
	- 0 : normal state
	- 1 : reset state

	Reset signal needs to be longer than 100ns.
*/
CTR_6002DR2_API void LMLL_TopSetLpfCalRst(bool state)
{
	getMainModule()->getTop()->setLpfCalRst(state);
}

/**
	@ingroup TopModule
	@brief Returns reset signal used at the beginning of calibration cycle.
	@retval 0 : normal state
	@retval 1 : reset state
*/
CTR_6002DR2_API bool LMLL_TopGetLpfCalRst()
{
	return  getMainModule()->getTop()->getLpfCalRst();
}

/**
	@ingroup TopModule
	@brief Enables or disables LPFCAL.
	@param state LPFCAL enabled
	- 0 : Block disabled (default)
	- 1 : Block enabled

	Should be enabled only during the RC calibration algorithm running.
*/
CTR_6002DR2_API void LMLL_TopSetLpfCalEn(bool state)
{
	getMainModule()->getTop()->setLpfCalEn(state);
}

/**
	@ingroup TopModule
	@brief Returns whether LPFCAL is enabled or disabled.
	@return LPFCAL enabled
	@retval 0 : Block disabled
	@retval 1 : Block enabled
*/
CTR_6002DR2_API bool LMLL_TopGetLpfCalEn()
{
	return  getMainModule()->getTop()->getLpfCalEn();
}

/**
	@ingroup TopModule
	@brief Enables or disables the enforce mode.
	@param enabled enforce mode enabled
*/
CTR_6002DR2_API void LMLL_TopSetLpfCalEnEnf(bool enabled)
{
	getMainModule()->getTop()->setLpfCalEnEnf(enabled);
}

/**
	@ingroup TopModule
	@brief Returns whether enforce mode is enabled or disabled.
*/
CTR_6002DR2_API bool LMLL_TopGetLpfCalEnEnf()
{
	return  getMainModule()->getTop()->getLpfCalEnEnf();
}

/**
	@ingroup TopModule
	@brief Sets FORCE_CODE_CAL_LPFCAL[2:0]: Input code coming from software.
	@param index code values from 0 to 7

	Will be passed to the output if ENF_EN_CAL_LPFCAL=1.
*/
CTR_6002DR2_API void LMLL_TopSetLpfCalCode(int index)
{
	getMainModule()->getTop()->setLpfCalCode(index);
}

/**
	@ingroup TopModule
	@brief returns FORCE_CODE_CAL_LPFCAL[2:0]:
*/
CTR_6002DR2_API int LMLL_TopGetLpfCalCode()
{
	return  getMainModule()->getTop()->getLpfCalCode();
}

/**
	@ingroup TopModule
	@brief Sets LPF bandwidth
	@param index value index from the list
	- 0 : 14 MHz
	- 1 : 10 MHz
	- 2 : 7 MHz
	- 3 : 6 MHz
	- 4 : 5 MHz
	- 5 : 4.375 MHz
	- 6 : 3.5 MHz
	- 7 : 3 MHz
	- 8 : 2.75 MHz
	- 9 : 2.5 MHz
	- 10 :  1.92 MHz
	- 11 : 1.5 MHz
	- 12 : 1.375 MHz
	- 13 : 1.25 MHz
	- 14 : 0.875 MHz
	- 15 : 0.75 MHz
*/
CTR_6002DR2_API void LMLL_TopSetLpfCalBw(int index)
{
	getMainModule()->getTop()->setLpfCalBw(index);
}

/**
	@ingroup TopModule
	@brief Returns LPF bandwidth
	@retval 0 : 14 MHz
	@retval 1 : 10 MHz
	@retval 2 : 7 MHz
	@retval 3 : 6 MHz
	@retval 4 : 5 MHz
	@retval 5 : 4.375 MHz
	@retval 6 : 3.5 MHz
	@retval 7 : 3 MHz
	@retval 8 : 2.75 MHz
	@retval 9 : 2.5 MHz
	@retval 10 :  1.92 MHz
	@retval 11 : 1.5 MHz
	@retval 12 : 1.375 MHz
	@retval 13 : 1.25 MHz
	@retval 14 : 0.875 MHz
	@retval 15 : 0.75 MHz
*/
CTR_6002DR2_API int LMLL_TopGetLpfCalBw()
{
	return  getMainModule()->getTop()->getLpfCalBw();
}

/**
	@ingroup TopModule
	@brief Enables or disables Top modules
	@param enabled Top modules enabled
*/
CTR_6002DR2_API void LMLL_TopSetPwrTopMods(bool enabled)
{
	getMainModule()->getTop()->setPwrTopMods(enabled);
}

/**
	@ingroup TopModule
	@brief Returns whether Top modules are enabled or disabled.
	@return Top modules enabled
*/
CTR_6002DR2_API bool LMLL_TopGetPwrTopMods()
{
	return  getMainModule()->getTop()->getPwrTopMods();
}

/**
	@ingroup TopModule
	@brief Enables or disables transmitter.
	@param enabled soft transmit enabled
	- 0 : transmitter powered down
	- 1 : trasmitter enabled
*/
CTR_6002DR2_API void LMLL_TopSetPwrSoftTx(bool enabled)
{
	getMainModule()->getTop()->setPwrSoftTx(enabled);
}

/**
	@ingroup TopModule
	@brief Returns whether Transmitter is enabled
	@return transmitter enabled
*/
CTR_6002DR2_API bool LMLL_TopGetPwrSoftTx()
{
	return  getMainModule()->getTop()->getPwrSoftTx();
}

/**
	@ingroup TopModule
	@brief Enables or disables receiver.
	@param enabled soft receive enabled
	- 0 : receiver powered down
	- 1 : receiver enabled
*/
CTR_6002DR2_API void LMLL_TopSetPwrSoftRx(bool enabled)
{
	getMainModule()->getTop()->setPwrSoftRx(enabled);
}

/**
	@ingroup TopModule
	@brief Returns whether Receiver is enabled.
	@return receiver enabled
*/
CTR_6002DR2_API bool LMLL_TopGetPwrSoftRx()
{
	return  getMainModule()->getTop()->getPwrSoftRx();
}

/**
	@ingroup TopModule
	@brief Sets power down control for top modules, PD_DCOREF_LPFCAL.
	@param state PD_DCOREF_LPFCAL enabled
	- 0 : PD_DCOREF_LPFCAL powered down.
	- 1 : PD_DCOREF_LPFCAL powered up.
*/
CTR_6002DR2_API void LMLL_TopSetPwrLpfCal(bool state)
{
	getMainModule()->getTop()->setPwrLpfCal(state);
}

/**
	@ingroup TopModule
	@brief Returns power down control for top modules, PD_DCOREF_LPFCAL.
	@return PD_DCOREF_LPFCAL enabled
	@retval 0 : PD_DCOREF_LPFCAL powered down.
	@retval 1 : PD_DCOREF_LPFCAL powered up.
*/
CTR_6002DR2_API bool LMLL_TopGetPwrLpfCal()
{
	return  getMainModule()->getTop()->getPwrLpfCal();
}

/**
	@ingroup TopModule
	@brief Sets power down control for top modules, RF loop back switch.
	@param state RF loop back switch enabled
	- 0 : RF loop back switch powered down.
	- 1 : RF loop back switch powered up.
*/
CTR_6002DR2_API void LMLL_TopSetPwrRfLbsw(bool state)
{
	getMainModule()->getTop()->setPwrRfLbsw(state);
}

/**
	@ingroup TopModule
	@brief Return power down control for top modules, RF loop back switch.
	@return RF loop back switch enabled
	@retval 0 : RF loop back switch powered down.
	@retval 1 : RF loop back switch powered up.
*/
CTR_6002DR2_API bool LMLL_TopGetPwrRfLbsw()
{
	return  getMainModule()->getTop()->getPwrRfLbsw();
}

/**
	@ingroup TopModule
	@brief Sets active calibration module address.
	@param index value index from the list
	- 0 : LPF tuning module
	- 1-7 : not used
*/
CTR_6002DR2_API void LMLL_TopSetDCCalAddr(int index)
{
	getMainModule()->getTop()->setDCCalAddr(index);
}

/**
	@ingroup TopModule
	@brief Returns DC calibration module address.
	@return module address
*/
CTR_6002DR2_API int LMLL_TopGetDCCalAddr()
{
	return  getMainModule()->getTop()->getDCCalAddr();
}

/*
	@ingroup TopModule
	@brief Sets DC calibration value.
	@param value calibration value

CTR_6002DR2_API void LMLL_TopSetCalVal(int value)
{
	getMainModule()->getTop()->setCalVal(value);
}
*/

/*
	@ingroup TopModule
	@brief Returns DC calibration value.
	@return calibration value

CTR_6002DR2_API int LMLL_TopGetCalVal()
{
	return  getMainModule()->getTop()->getCalVal();
}
*/

/**
	@ingroup TopModule
	@brief Activates reset signal.
*/
CTR_6002DR2_API void LMLL_TopResetOn()
{
	getMainModule()->getTop()->swResetOn();
}
/**
	@ingroup TopModule
	@brief Deactiveates reset signal.
*/
CTR_6002DR2_API void LMLL_TopResetOff()
{
	getMainModule()->getTop()->swResetOff();
}

/**
	@ingroup TopModule
	@brief Sets BB loopback control
	@param index value index from the list
	- 0 : Disabled
	- 1 : Loopback to LPF input
	- 2 : Loopback to VGA2 input
	- 3 : Loopback to Rx Out Pins
*/
CTR_6002DR2_API void LMLL_TopSetBBLB(int index)
{
	getMainModule()->getTop()->setBBLB(index);
}

/**
	@ingroup TopModule
	@brief Returns BB loopback control
	@retval 0 : Disabled
	@retval 1 : Loopback to LPF input
	@retval 2 : Loopback to VGA2 input
	@retval 3 : Loopback to Rx Out Pins
*/
CTR_6002DR2_API int LMLL_TopGetBBLB()
{
	return  getMainModule()->getTop()->getBBLB();
}

/**
	@ingroup TopModule
	@brief Selects the clock for LPF tuning module.
	@param index value index from the list
	- 0 : 40 MHz clock generated from Tx PLL output
	- 1 : use PLL refernece clock
*/
CTR_6002DR2_API void LMLL_TopSetCLKSEL_LPFCAL(int index)
{
	getMainModule()->getTop()->setCLKSEL_LPFCAL(index);
}

/**
	@ingroup TopModule
	@brief Returns the clock of LPF tuning module.
	@retval 0 : 40 MHz clock generated from Tx PLL output
	@retval 1 : use PLL refernece clock
*/
CTR_6002DR2_API int LMLL_TopGetCLKSEL_LPFCAL()
{
	return  getMainModule()->getTop()->getCLKSEL_LPFCAL();
}

/**
	@ingroup TopModule
	@brief Set power down on chip LPF tuning clock generation block
	@param state
	- 0 : powered up
	- 1 : powered down
*/
CTR_6002DR2_API void LMLL_TopSetPD_CLKLPFCAL(bool state)
{
	getMainModule()->getTop()->setPD_CLKLPFCAL(state);
}

/**
	@ingroup TopModule
	@brief Returns power down on chip LPF tuning clock generation block
	@retval 0 : powered up
	@retval 1 : powered down
*/
CTR_6002DR2_API bool LMLL_TopGetPD_CLKLPFCAL()
{
	return  getMainModule()->getTop()->getPD_CLKLPFCAL();
}

/**
	@ingroup TopModule
	@brief Sets RX out/ADC in high-Z switch control.
	@param index value index from the list
	- 0 : switch open (RX output/ADC input chip pins disconnected)
	- 1 : switch closed, RXVGA2 should be powered off first
*/
CTR_6002DR2_API void LMLL_TopSetRXOUTSW(int index)
{
	getMainModule()->getTop()->setRXOUTSW(index);
}

/**
	@ingroup TopModule
	@brief Returns RX out/ADC in high-Z switch control.
	@retval 0 : switch open (RX output/ADC input chip pins disconnected)
	@retval 1 : switch closed
*/
CTR_6002DR2_API int LMLL_TopGetRXOUTSW()
{
	return  getMainModule()->getTop()->getRXOUTSW();
}

/**
	@ingroup TopModule
	@brief Sets frequency/Time division duplexing selection
	@param mode
	- 0 : FDD mode
	- 1 : TDD mode
*/
CTR_6002DR2_API void LMLL_TopSetFDDTDD(int mode)
{
	getMainModule()->getTop()->setFDDTDD(mode);
}

/**
	@ingroup TopModule
	@brief Returns frequency/Time division duplexing selection
	@retval 0 : FDD mode (default)
	@retval 1 : TDD mode
*/
CTR_6002DR2_API int LMLL_TopGetFDDTDD()
{
	return  getMainModule()->getTop()->getFDDTDD();
}

/**
	@ingroup TopModule
	@brief Sets TDD mode selection if FDDTDD=1
	@param mode TDD mode
	- 0 : TDD transmit mode
	- 1 : TDD receive mode
*/
CTR_6002DR2_API void LMLL_TopSetTDDMOD(int mode)
{
	getMainModule()->getTop()->setTDDMOD(mode);
}

/**
	@ingroup TopModule
	@brief Returns TDD mode selection
	@retval 0 : TDD transmit mode
	@retval 1 : TDD receive mode
*/
CTR_6002DR2_API int LMLL_TopGetTDDMOD()
{
	return  getMainModule()->getTop()->getTDDMOD();
}

/**
	@ingroup TopModule
	@brief Sets XCO buffer power state.
	@param state buffer power state
	- 0 : buffer powered up (default)
	- 1 : buffer powered down
*/
CTR_6002DR2_API void LMLL_TopSetPDXCOBUF(bool state)
{
	getMainModule()->getTop()->setPDXCOBUF(state);
}

/**
	@ingroup TopModule
	@brief Returns XCO buffer power state.
	@retval 0 : buffer powered up
	@retval : buffer powered down
*/
CTR_6002DR2_API bool LMLL_TopGetPDXCOBUF()
{
	return  getMainModule()->getTop()->getPDXCOBUF();
}

/**
	@ingroup TopModule
	@brief Enables or disables XCO buffer self biasing.
	@param state self biasing state
	- 0 : self biasing disabled
	- 1 : self biasing enabled
*/
CTR_6002DR2_API void LMLL_TopSetSLFBXCOBUF(bool state)
{
	getMainModule()->getTop()->setSLFBXCOBUF(state);
}

/**
	@ingroup TopModule
	@brief Returns XCO buffer self biasing state.
	@retval 0 : self biasing disabled
	@retval 1 : self biasing enabled
*/
CTR_6002DR2_API bool LMLL_TopGetSLFBXCOBUF()
{
	return  getMainModule()->getTop()->getSLFBXCOBUF();
}

/**
	@ingroup TopModule
	@brief Sets XCO buffer bypass state
	@param state bypass state
	- 0 : buffer active (default)
	- 1 : buffer bypassed
*/
CTR_6002DR2_API void LMLL_TopSetBYPXCOBUF(bool state)
{
	getMainModule()->getTop()->setBYPXCOBUF(state);
}

/**
	@ingroup TopModule
	@brief Returns XCO buffer bypass state
	@retval 0 : buffer active (default)
	@retval 1 : buffer bypassed
*/
CTR_6002DR2_API bool LMLL_TopGetBYPXCOBUF()
{
	return  getMainModule()->getTop()->getBYPXCOBUF();
}

/**
	@ingroup TopModule
	@brief Returns DC calibration values
	@param &calibVal calibration value
	@param &lockPattern lock pattern
	@param &calibStatus calibration status
	@param &compValue comparator value
*/
CTR_6002DR2_API void LMLL_TopGetDCCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue)
{
	getMainModule()->getTop()->DCGetCalibrationData(calibVal, lockPattern, calibStatus, compValue);
}

/*
CTR_6002DR2_API int LMLL_TopGetDC_REGVAL()
{
	return  getMainModule()->getTop()->getDC_REGVAL();
}
*/

/**
	@ingroup TopModule
	@brief Reads value of the cal_core block in the LPF which calibrates the RC time constant.
	@return RCCAL_LPFCAL
*/
CTR_6002DR2_API int LMLL_TopGetRCCAL_LPFCAL()
{
	int temp = 0;
	getMainModule()->getTop()->ReadRCCALValues(temp);
	return temp;
}

/*
CTR_6002DR2_API int LMLL_TopGetDC_LOCK()
{
	return  getMainModule()->getTop()->getDC_LOCK();
}

CTR_6002DR2_API int LMLL_TopGetDC_CLBR_DONE()
{
	return  getMainModule()->getTop()->getDC_CLBR_DONE();
}

CTR_6002DR2_API int LMLL_TopGetDC_UD()
{
	return  getMainModule()->getTop()->getDC_UD();
}
*/

/*
CTR_6002DR2_API int LMLL_TopGetDC_CNTVAL()
{
	return  getMainModule()->getTop()->getDC_CNTVAL();
}
*/

/**
	@ingroup TopModule
	@brief Reset DC calibration.
*/
CTR_6002DR2_API void LMLL_TopDCResetCalibration()
{
	getMainModule()->getTop()->DCResetCalibration();
}

/**
	@ingroup TopModule
	@brief Loads value to module selected by LMLL_TopSetDCCalAddr()
	@param value value to load
*/
CTR_6002DR2_API void LMLL_TopDCLoadValues(unsigned int value)
{
	getMainModule()->getTop()->DCLoadValues(value);
}

/**
	@ingroup TopModule
	@brief Starts DC calibration.
*/
CTR_6002DR2_API void LMAL_TopDCStartCalibration()
{
	getMainModule()->getTop()->DCStartCalibration();
}

/**
	@ingroup TopModule
	@brief Reads and returns DC calibration values from the chip.
	@param &calibVal calibration value
	@param &lockPattern lock pattern
	@param &calibStatus calibration status
	@param &compValue comparator value
*/
CTR_6002DR2_API void LMLL_TopDCReadValues(int &calibVal, int &lockPattern, int &calibStatus, int &compValue)
{
	getMainModule()->getTop()->DCGetCalibrationData(calibVal, lockPattern, calibStatus, compValue);
}

/*
CTR_6002DR2_API void LMLL_TopDownloadAllDCCalValues()
{
	getMainModule()->getTop()->DownloadAllDCCalValues();
}

CTR_6002DR2_API void LMLL_TopSetCalAddr(int Addr)
{
	getMainModule()->getTop()->SetCalAddr(Addr);
}

CTR_6002DR2_API void LMLL_TopStartCalibration(int Addr)
{
	getMainModule()->getTop()->StartCalibration(Addr);
}

CTR_6002DR2_API char LMLL_TopGetCalStatus()
{
	return  getMainModule()->getTop()->GetCalStatus();
}

CTR_6002DR2_API void LMLL_TopSetCalDefaults()
{
	getMainModule()->getTop()->SetCalDefaults();
}
*/

/*
CTR_6002DR2_API void LMLL_TopEnableAllSPIClocks()
{
	getMainModule()->getTop()->EnableAllSPIClocks();
}

CTR_6002DR2_API void LMLL_TopEnableSPIClocksByMask(int mask)
{
	getMainModule()->getTop()->EnableSPIClocksByMask(mask);
}

CTR_6002DR2_API void LMLL_TopRestoreAllSPIClocks()
{
	getMainModule()->getTop()->RestoreAllSPIClocks();
}
*/

/*
CTR_6002DR2_API void LMLL_Top_SetTia2OutOn()
{
	getMainModule()->getTop()->CustSet_Tia2OutON();
}

CTR_6002DR2_API void LMLL_Top_SetTia2OutOff()
{
	getMainModule()->getTop()->CustSet_Tia2OutOFF();
}
*/

/**
	@ingroup TopModule
	@brief Sets LPF bandwidth
	@param index value index from the list
	- 0 : 14 MHz
	- 1 : 10 MHz
	- 2 : 7 MHz
	- 3 : 6 MHz
	- 4 : 5 MHz
	- 5 : 4.375 MHz
	- 6 : 3.5 MHz
	- 7 : 3 MHz
	- 8 : 2.75 MHz
	- 9 : 2.5 MHz
	- 10 :  1.92 MHz
	- 11 : 1.5 MHz
	- 12 : 1.375 MHz
	- 13 : 1.25 MHz
	- 14 : 0.875 MHz
	- 15 : 0.75 MHz
*/
CTR_6002DR2_API void LMLL_Top_SetLPFBandwidth(int index)
{
	getMainModule()->getTop()->CustSet_LPFBandwidth(index);
}

/**
	@ingroup TopModule
	@brief Enables or disables Top modules.
	@param on power on state
*/
CTR_6002DR2_API void LMAL_Top_PowerOn(bool on)
{
	getMainModule()->getTop()->TopPowerOn(on);
}

/*
CTR_6002DR2_API void LMLL_Top_SetEnableLPFCAL(bool On)
{
	getMainModule()->getTop()->CustSet_EnableLPFCAL(On);
}

CTR_6002DR2_API void LMLL_Top_SetResetLPFCAL(bool Active)
{
	getMainModule()->getTop()->CustSet_ResetLPFCAL(Active);
}

CTR_6002DR2_API void LMLL_Top_GetLPFCALVal(int &DCCALVal, int &LPFCALVal)
{
	getMainModule()->getTop()->CustGet_LPFCALVal(DCCALVal, LPFCALVal);
}

CTR_6002DR2_API void LMLL_Top_SetPLLCLKOUT(bool Enabled)
{
	getMainModule()->getTop()->CustSet_PLLCLKOUT(Enabled);
}

CTR_6002DR2_API bool LMLL_Top_SetSofTxOnOff(bool On)
{
	return  getMainModule()->getTop()->CustSet_SofTxOnOff(On);
}

CTR_6002DR2_API bool LMLL_Top_SetSofRxOnOff(bool On)
{
	return  getMainModule()->getTop()->CustSet_SofRxOnOff(On);
}
*/

//==============================================================================
// End of Top Module

// RxVGA2 Module
//==============================================================================
/**
	@ingroup RxVGA2
	@brief Returns RxVGA2 module address.
*/
CTR_6002DR2_API char LMLL_RxVGA2GetAddr()
{
	return  getMainModule()->getRxVga2()->getAddr();
}

/*
CTR_6002DR2_API void LMLL_RxVGA2StartCalibration(int Addr)
{
	getMainModule()->getRxVga2()->StartCalibration(Addr);
}
*/

/*
CTR_6002DR2_API char LMLL_RxVGA2GetCalStatus()
{
	return  getMainModule()->getRxVga2()->GetCalStatus();
}
*/

/*
CTR_6002DR2_API void LMLL_RxVGA2SetCalDefaults()
{
	getMainModule()->getRxVga2()->SetCalDefaults();
}
*/

/**
	@ingroup RxVGA2
	@brief Reset RxVGA2 DC calibration.
*/
CTR_6002DR2_API void LMLL_RxVGA2DCResetCalibration()
{
	getMainModule()->getRxVga2()->DCResetCalibration();
}

/**
	@ingroup RxVGA2
	@brief Loads value to module selected by LMLL_RxVGA2SetDCCalAddr()
	@param value value to load
*/
CTR_6002DR2_API void LMLL_RxVGA2DCLoadValues( unsigned int value)
{
	getMainModule()->getRxVga2()->DCLoadValues( value );
}


/**
	@ingroup RxVGA2
	@brief Starts RxVGA2 DC calibration.
*/
CTR_6002DR2_API void LMLL_RxVGA2DCStartCalibration()
{
	getMainModule()->getRxVga2()->DCStartCalibration();
}

/**
	@ingroup RxVGA2
	@brief Reads and returns DC calibration values from the chip.
	@param &calibVal calibration value
	@param &lockPattern lock pattern
	@param &calibStatus calibration status
	@param &compValue comparator value
*/
CTR_6002DR2_API void LMLL_RxVGA2DCReadValues(int &calibVal, int &lockPattern, int &calibStatus, int &compValue)
{
	getMainModule()->getRxVga2()->DCGetCalibrationData(calibVal, lockPattern, calibStatus, compValue);
}

/**
	@ingroup RxVGA2
	@brief Enables or disables RxVGA2 modules
	@param on power on state
*/
CTR_6002DR2_API void LMAL_RxVGA2_PowerOn(bool on)
{
	getMainModule()->getRxVga2()->RxVGA2PowerOn(on);
}

/**
	@ingroup RxVGA2
	@brief Sets RxVGA2 gain
	@param index value index from the list
	- 0 : 0 dB
	- 1 : 3 dB
	- 2 : 6 dB
	- ...
	- 10 : 30 dB
	- ...
	- 20 : 60 dB
*/
CTR_6002DR2_API void LMLL_RxVGA2SetRXVGA2Gain(int index)
{
	getMainModule()->getRxVga2()->setRXVGA2Gain(index);
}
/**
	@ingroup RxVGA2
	@brief Returns RxVGA2 gain
	@retval 0 : 0 dB
	@retval 1 : 3 dB
	@retval 2 : 6 dB
	@retval ...
	@retval 10 : 30 dB
	@retval ...
	@retval 20 : 60 dB
*/
CTR_6002DR2_API int LMLL_RxVGA2GetRXVGA2Gain()
{
	return  getMainModule()->getRxVga2()->getRXVGA2Gain();
}

/**
	@ingroup RxVGA2
	@brief Enables or disables RxVGA2 modules.
	@param state RxVGA2 modules enabled
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrVGA2Mods(bool state)
{
	getMainModule()->getRxVga2()->setPwrVGA2Mods(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether RxVGA2 modules are enabled or disabled.
	@return RxVGA2 modules enabled
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrVGA2Mods()
{
	return  getMainModule()->getRxVga2()->getPwrVGA2Mods();
}

/**
	@ingroup RxVGA2
	@brief Sets RxVGA2 decode mode.
	@param mode decode mode
	- 0 : decode control signals (default)
	- 1 : use control signals from test mode registers
*/
CTR_6002DR2_API void LMLL_RxVGA2SetDecode(int mode)
{
	getMainModule()->getRxVga2()->setDecode(mode);
}

/**
	@ingroup RxVGA2
	@brief Returns RxVGA2 decode mode.
	@retval 0 : decode control signals (default)
	@retval 1 : use control signals from test mode registers
*/
CTR_6002DR2_API int LMLL_RxVGA2GetDecode()
{
	return  getMainModule()->getRxVga2()->getDecode();
}

/**
	@ingroup RxVGA2
	@brief Sets RxVGA2 gain
	@param index value index from the list
	- 0 : 0 dB
	- 1 : 3 dB
	- 2 : 6 dB
	- ...
	- 10 : 30 dB
	- ...
	- 20 : 60 dB

	Not recommended to be used above 30dB.
*/
CTR_6002DR2_API void LMLL_RxVGA2SetVga2G_u(int index)
{
	getMainModule()->getRxVga2()->setVga2G_u(index);
}

/**
	@ingroup RxVGA2
	@brief Returns RxVGA2 gain
	@retval 0 : 0 dB
	@retval 1 : 3 dB
	@retval 2 : 6 dB
	@retval ...
	@retval 10 : 30 dB
	@retval ...
	@retval 20 : 60 dB
*/
CTR_6002DR2_API int LMLL_RxVGA2GetVga2G_u()
{
	return  getMainModule()->getRxVga2()->getVga2G_u();
}

/**
	@ingroup RxVGA2
	@brief Enables or disables RxVGA2 DC current regulator
	@param state regulator state
	- 0 : powered down
	- 1 : powered up
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCCurrR(bool state)
{
	getMainModule()->getRxVga2()->setPwrDCCurrR(state);
}

/**
	@ingroup RxVGA2
	@brief Returns RxVGA2 DC current regulator state
	@retval 0 : powered down
	@retval 1 : powered up (default)
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCCurrR()
{
	return  getMainModule()->getRxVga2()->getPwrDCCurrR();
}

/**
	@ingroup RxVGA2
	@brief Enables or disables RxVGA2 DC calibration DAC for VGA2B.
	@param state
	- 0 : powered down
	- 1 : powered up (default)
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCDACB(bool state)
{
	getMainModule()->getRxVga2()->setPwrDCDACB(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether RxVGA2 DC calibration DAC for VGA2B is enabled or disabled.
	@retval 0 : powered down
	@retval 1 : powered up (default)
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCDACB()
{
	return  getMainModule()->getRxVga2()->getPwrDCDACB();
}

/**
	@ingroup RxVGA2
	@brief Sets DC calibration comparator for VGA2B.
	@param state
	- 0 : powered down
	- 1 : powered up (default)
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCCmpB(bool state)
{
	getMainModule()->getRxVga2()->setPwrDCCmpB(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether DC calibration comparator for VGA2B is enabled or disabled.
	@retval 0 : powered down
	@retval 1 : powered up (default)
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCCmpB()
{
	return  getMainModule()->getRxVga2()->getPwrDCCmpB();
}

/**
	@ingroup RxVGA2
	@brief Enables or disables RxVGA2 DC calibration DAC for VGA2A.
	@param state
	- 0 : powered down
	- 1 : powered up (default)
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCDACA(bool state)
{
	getMainModule()->getRxVga2()->setPwrDCDACA(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether RxVGA2 DC calibration DAC for VGA2A is enabled or disabled.
	@retval 0 : powered down
	@retval 1 : powered up (default)
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCDACA()
{
	return  getMainModule()->getRxVga2()->getPwrDCDACA();
}

/**
	@ingroup RxVGA2
	@brief Returns whether RxVGA2 DC calibration DAC for VGA2A is enabled or disabled.
	@retval 0 : powered down
	@retval 1 : powered up (default)
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCCmpA(bool state)
{
	getMainModule()->getRxVga2()->setPwrDCCmpA(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether DC calibration comparator for VGA2A is enabled or disabled.
	@retval 0 : powered down
	@retval 1 : powered up (default)
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCCmpA()
{
	return  getMainModule()->getRxVga2()->getPwrDCCmpA();
}

/**
	@ingroup RxVGA2
	@brief Enables or disables Band gap.
	@param state band gap state
	- 0 : powered down
	- 1 : powered up
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrBG(bool state)
{
	getMainModule()->getRxVga2()->setPwrBG(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether band gap is enabled or disabled.
	@retval 0 : powered down
	@retval 1 : powered up
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrBG()
{
	return  getMainModule()->getRxVga2()->getPwrBG();
}

/**
	@ingroup RxVGA2
	@brief Sets output buffer state in both RXVGAs.
	@param state buffer state
	- 0 : powered down
	- 1 : powered up
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrBypAB(bool state)
{
	getMainModule()->getRxVga2()->setPwrBypAB(state);
}

/**
	@ingroup RxVGA2
	@brief Returns output buffer state in both RXVGAs.
	@retval 0 : powered down
	@retval 1 : powered up
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrBypAB()
{
	return  getMainModule()->getRxVga2()->getPwrBypAB();
}

/**
	@ingroup RxVGA2
	@brief Enables or disables RxVGA2B.
	@param state RxVGA2B enabled
	- 0 : disabled (powered down)
	- 1 : enabled (powered up)
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrBypB(bool state)
{
	getMainModule()->getRxVga2()->setPwrBypB(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether RxVGA2B is enabled or disabled.
	@retval 0 : disabled (powered down)
	@retval 1 : enabled (powered up)
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrBypB()
{
	return  getMainModule()->getRxVga2()->getPwrBypB();
}

/**
	@ingroup RxVGA2
	@brief Enables or disables RxVGA2B.
	@param state RxVGA2A enabled
	- 0 : disabled (powered down)
	- 1 : enabled (powered up)
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrBypA(bool state)
{
	getMainModule()->getRxVga2()->setPwrBypA(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether RxVGA2A is enabled or disabled.
	@retval 0 : disabled (powered down)
	@retval 1 : enabled (powered up)
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrBypA()
{
	return  getMainModule()->getRxVga2()->getPwrBypA();
}

/**
	@ingroup RxVGA2
	@brief Enables or disables current reference.
	@param state current reference enabled
	- 0 : disabled (powered down)
	- 1 : enabled ( powered up)
*/
CTR_6002DR2_API void LMLL_RxVGA2SetPwrCurrRef(bool state)
{
	getMainModule()->getRxVga2()->setPwrCurrRef(state);
}

/**
	@ingroup RxVGA2
	@brief Returns whether current reference is enabled or disabled.
	@retval 0 : disabled (powered down)
	@retval 1 : enabled ( powered up)
*/
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrCurrRef()
{
	return  getMainModule()->getRxVga2()->getPwrCurrRef();
}

/**
	@ingroup RxVGA2
	@brief Sets the gain of second VGA2 stage (VGA2B).
	@param index value index from the list
	- 0 : 0 dB (default)
	- 1 : 3 dB
	- ...
	- 9 : 27 dB
	- 10 : 30 dB
*/
CTR_6002DR2_API void LMLL_RxVGA2SetVga2GB_t(int index)
{
	getMainModule()->getRxVga2()->setVga2GB_t(index);
}

/**
	@ingroup RxVGA2
	@brief Returns the gain of second VGA2 stage (VGA2B).
	@retval 0 : 0 dB (default)
	@retval 1 : 3 dB
	@retval ...
	@retval 9 : 27 dB
	@retval 10 : 30 dB
*/
CTR_6002DR2_API int LMLL_RxVGA2GetVga2GB_t()
{
	return  getMainModule()->getRxVga2()->getVga2GB_t();
}

/**
	@ingroup RxVGA2
	@brief Sets the gain of first VGA2 stage (VGA2A).
	@param index value index from the list
	- 0 : 0 dB (default)
	- 1 : 3 dB
	- ...
	- 9 : 27 dB
	- 10 : 30 dB
*/
CTR_6002DR2_API void LMLL_RxVGA2SetVga2GA_t(int index)
{
	getMainModule()->getRxVga2()->setVga2GA_t(index);
}

/**
	@ingroup RxVGA2
	@brief Returns the gain of first VGA2 stage (VGA2A).
	@retval 0 : 0 dB (default)
	@retval 1 : 3 dB
	@retval ...
	@retval 9 : 27 dB
	@retval 10 : 30 dB
*/
CTR_6002DR2_API int LMLL_RxVGA2GetVga2GA_t()
{
	return  getMainModule()->getRxVga2()->getVga2GA_t();
}

/**
	@ingroup RxVGA2
	@brief Sets Active calibration module address
	@param index module address
	- 0 : DC reference module.
	- 1 : First gain stage (VGA2A), Q channel.
	- 2 : First gain stage (VGA2A), I channel.
	- 3 : Second gain stage (VGA2B), Q channel.
	- 4 : Second gain stage (VGA2B), I channel.
*/
CTR_6002DR2_API void LMLL_RxVGA2SetDCCalAddr(int index)
{
	getMainModule()->getRxVga2()->setDCCalAddr(index);
}

/**
	@ingroup RxVGA2
	@brief Returns Active calibration module address
	@retval 0 : DC reference module.
	@retval 1 : First gain stage (VGA2A), Q channel.
	@retval 2 : First gain stage (VGA2A), I channel.
	@retval 3 : Second gain stage (VGA2B), Q channel.
	@retval 4 : Second gain stage (VGA2B), I channel.
*/
CTR_6002DR2_API int LMLL_RxVGA2GetDCCalAddr()
{
	return  getMainModule()->getRxVga2()->getDCCalAddr();
}

/*
	@ingroup RxVGA2
	@brief Set DC calibration value.
	@param index calibration value

CTR_6002DR2_API void LMLL_RxVGA2SetCalVal(int index)
{
	getMainModule()->getRxVga2()->setCalVal(index);
}
*/

/**
	@ingroup RxVGA2
	@brief Returns DC calibration value.
	@return calibration value

CTR_6002DR2_API int LMLL_RxVGA2GetCalVal()
{
	return  getMainModule()->getRxVga2()->getCalVal();
}
*/

/**
	@ingroup RxVGA2
	@brief Sets RXVGA2 output common mode voltage.
	@param index value index from the list
	- 0 : 1.18V
	- 1 : 1.14V
	- 2 : 1.10V
	- ...
	- 6 : 0.94V
	- 7 : 0.90V (default)
	- 8 : 0.86V
	- ...
	- 13 : 0.66V
	- 14 : 0.62V
*/
CTR_6002DR2_API void LMLL_RxVGA2SetVCM(int index)
{
	getMainModule()->getRxVga2()->setVCM(index);
}

/**
	@ingroup RxVGA2
	@brief Returns RXVGA2 output common mode voltage.
	@retval 0 : 1.18V
	@retval 1 : 1.14V
	@retval 2 : 1.10V
	@retval ...
	@retval 6 : 0.94V
	@retval 7 : 0.90V (default)
	@retval 8 : 0.86V
	@retval ...
	@retval 13 : 0.66V
	@retval 14 : 0.62V
*/
CTR_6002DR2_API int LMLL_RxVGA2GetVCM()
{
	return  getMainModule()->getRxVga2()->getVCM();
}

/**
	@ingroup RxVGA2
	@brief Reads DC calibration values from the chip.
	@param &dcRegVal calibration value
	@param &lockPattern lock pattern
	@param &calibStatus calibration status
	@param &compValue comparator value
*/
CTR_6002DR2_API void LMLL_RxVGA2GetDCCalibrationData(int &dcRegVal, int &lockPattern, int &calibStatus, int &compValue)
{
	getMainModule()->getRxVga2()->DCGetCalibrationData(dcRegVal, lockPattern, calibStatus, compValue);
/*
	dcRegVal = getMainModule()->getRxVga2()->lbDC_REGVAL;
	lockPattern = getMainModule()->getRxVga2()->lblDC_LOCK;
	calibStatus = getMainModule()->getRxVga2()->lblDC_CLBR_DONE;
	compValue = getMainModule()->getRxVga2()->lblDC_UD;
*/
}

//==============================================================================
// End of RxVGA2 Module

// RxFE Module
//==============================================================================
/**
	@ingroup RxFE
	@brief Returns RxFE module address.
	@return RxFE address
*/
CTR_6002DR2_API char LMLL_RxFEGetAddr()
{
	return  getMainModule()->getRxFe()->getAddr();
}

/**
	@ingroup RxFE
	@brief Sets active LNA.
	@param index value index from the list
	- 0 : All LNA'a disabled
	- 1 : LNA1 active
	- 2 : LNA2 active
	- 3 : LNA3 active
*/
CTR_6002DR2_API void LMLL_RxFESetActiveLNA(int index)
{
	getMainModule()->getRxFe()->CustSet_ActiveLNA(index);
}

/**
	@ingroup RxFE
	@brief Enables or disables RxFE LNA
	@param on LNA power on state
*/
CTR_6002DR2_API void LMAL_RxFE_LNAPowerOn(bool on)
{
	getMainModule()->getRxFe()->LNAPowerOn(on);
}

/**
	@ingroup RxFE
	@brief Enables or disables RxFE modules.
	@param on power on state
*/
CTR_6002DR2_API void LMAL_RxFE_PowerOn(bool on)
{
	getMainModule()->getRxFe()->PowerOn(on);
}

/*
CTR_6002DR2_API void LMLL_RxFE_SetDCOffsetCancellationI(int ind)
{
	getMainModule()->getRxFe()->CustSet_DCOffsetCancellationI(ind);
}

CTR_6002DR2_API void LMLL_RxFE_SetDCOffsetCancellationQ(int ind)
{
	getMainModule()->getRxFe()->CustSet_DCOffsetCancellationQ(ind);
}

CTR_6002DR2_API int LMLL_RxFE_GetDCOffsetCancellationI()
{
	return  getMainModule()->getRxFe()->CustGet_DCOffsetCancellationI();
}

CTR_6002DR2_API int LMLL_RxFE_GetDCOffsetCancellationQ()
{
	return  getMainModule()->getRxFe()->CustGet_DCOffsetCancellationQ();
}
*/

/**
	@ingroup RxFE
	@brief Sets RxFE decode mode.
	@param index value index from the list
	- 0 : decode control signals (default)
	- 1 : use control signals from test mode registers.
*/
CTR_6002DR2_API void LMLL_RxFESetDecode(int index)
{
	getMainModule()->getRxFe()->setDecode(index);
}

/**
	@ingroup RxFE
	@brief Returns RxFE decode mode.
	@retval 0 : decode control signals (default)
	@retval 1 : use control signals from test mode registers.
*/
CTR_6002DR2_API int LMLL_RxFEGetDecode()
{
	return  getMainModule()->getRxFe()->getDecode();
}

/**
	@ingroup RxFE
	@brief Enables or disables RxFE modules.
	@param state modules enabled
*/
CTR_6002DR2_API void LMLL_RxFESetPwrRxFeMods(bool state)
{
	getMainModule()->getRxFe()->setPwrRxFeMods(state);
}

/**
	@ingroup RxFE
	@brief Returns whether RxFE modules are enabled or disabled.
	@return RxFE modules enabled
*/
CTR_6002DR2_API bool LMLL_RxFEGetPwrRxFeMods()
{
	return  getMainModule()->getRxFe()->getPwrRxFeMods();
}

/**
	@ingroup RxFE
	@brief Selects the input to the mixer.
	@param index value index from the list
	- 0 : input 2 is selected, connected to pads
	- 1 : input 1 is selected, shorted on-chip to LNA internal output (default)
*/
CTR_6002DR2_API void LMLL_RxFESetIN1SEL_MIX_RXFE(int index)
{
	getMainModule()->getRxFe()->setIN1SEL_MIX_RXFE(index);
}

/**
	@ingroup RxFE
	@brief Returns the input to the mixer.
	@retval 0 : input 2 is selected, connected to pads
   	@retval 1 : input 1 is selected, shorted on-chip to LNA internal output
*/
CTR_6002DR2_API int LMLL_RxFEGetIN1SEL_MIX_RXFE()
{
	return  getMainModule()->getRxFe()->getIN1SEL_MIX_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets DC offset cancellation for I channel.
	@param index value index from the list
	- 0 : -63
	- 1 : -62
	- ...
	- 127 : 63
*/
CTR_6002DR2_API void LMLL_RxFESetDCOFF_I_RXFE(int index)
{
	getMainModule()->getRxFe()->setDCOFF_I_RXFE(index);
}

/**
	@ingroup RxFE
	@brief Returns DC offset cancellation for I channel.
	@retval 0 : -63
	@retval 1 : -62
	@retval ...
	@retval 127 : 63
*/
CTR_6002DR2_API int LMLL_RxFEGetDCOFF_I_RXFE()
{
	return  getMainModule()->getRxFe()->getDCOFF_I_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the internal load for the LNA.
	@param state internal load state
	- 1 : internal load is active (default)
	- 0 : internal node is disabled.
*/
CTR_6002DR2_API void LMLL_RxFESetINLOAD_LNA_RXFE(bool state)
{
	getMainModule()->getRxFe()->setINLOAD_LNA_RXFE(state);
}

/**
	@ingroup RxFE
	@brief Returns the internal load for the LNA.
	@retval 1 : internal load is active (default)
	@retval 0 : internal node is disabled.
*/
CTR_6002DR2_API bool LMLL_RxFEGetINLOAD_LNA_RXFE()
{
	return  getMainModule()->getRxFe()->getINLOAD_LNA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets DC offset cancellation for Q channel.
	@param index value index from the list
	- 0 : -63
	- 1 : -62
	- ...
	- 127 : 63
*/
CTR_6002DR2_API void LMLL_RxFESetDCOFF_Q_RXFE(int index)
{
	getMainModule()->getRxFe()->setDCOFF_Q_RXFE(index);
}

/**
	@ingroup RxFE
	@brief Returns DC offset cancellation for Q channel.
	@retval 0 : -63
	@retval 1 : -62
	@retval ...
	@retval 127 : 63
*/
CTR_6002DR2_API int LMLL_RxFEGetDCOFF_Q_RXFE()
{
	return  getMainModule()->getRxFe()->getDCOFF_Q_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the external load for the LNA.
	@param state external load state
	- 1 : external load is active
	- 0 : external node is disabled (default)
*/
CTR_6002DR2_API void LMLL_RxFESetXLOAD_LNA_RXFE(bool state)
{
	getMainModule()->getRxFe()->setXLOAD_LNA_RXFE(state);
}

/**
	@ingroup RxFE
	@brief Returns the external load for the LNA.
	@retval 1 : external load is active
	@retval 0 : external node is disabled (default)
*/
CTR_6002DR2_API bool LMLL_RxFEGetXLOAD_LNA_RXFE()
{
	return  getMainModule()->getRxFe()->getXLOAD_LNA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets IP2 cancellation for I channel.
	@param index value index from the list
    - 0 : -63
	- 1 : -62
	- ...
	- 127 : 63
*/
CTR_6002DR2_API void LMLL_RxFESetIP2TRIM_I_RXFE(int index)
{
	getMainModule()->getRxFe()->setIP2TRIM_I_RXFE(index);
}

/**
	@ingroup RxFE
	@brief Returns IP2 cancellation for I channel.
	@retval 0 : -63
	@retval 1 : -62
	@retval ...
	@retval 127 : 63
*/
CTR_6002DR2_API int LMLL_RxFEGetIP2TRIM_I_RXFE()
{
	return  getMainModule()->getRxFe()->getIP2TRIM_I_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets IP2 cancellation for Q channel.
	@param index value index from the list
    - 0 : -63
	- 1 : -62
	- ...
	- 127 : 63
*/
CTR_6002DR2_API void LMLL_RxFESetIP2TRIM_Q_RXFE(int index)
{
	getMainModule()->getRxFe()->setIP2TRIM_Q_RXFE(index);
}

/**
	@ingroup RxFE
	@brief Returns IP2 cancellation for Q channel.
	@retval 0 : -63
	@retval 1 : -62
	@retval ...
	@retval 127 : 63
*/
CTR_6002DR2_API int LMLL_RxFEGetIP2TRIM_Q_RXFE()
{
	return  getMainModule()->getRxFe()->getIP2TRIM_Q_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets LNA gain mode.
	@param index value index from the list
	- 0 : LNA bypassed
	- 1 : Mid gain
	- 2 : Max gain
*/
CTR_6002DR2_API void LMLL_RxFESetG_LNA_RXFE(int index)
{
	getMainModule()->getRxFe()->setG_LNA_RXFE(index);
}

/**
	@ingroup RxFE
	@brief Returns LNA gain mode.
	@retval 0 : LNA bypassed
	@retval 1 : Mid gain
	@retval 2 : Max gain
*/
CTR_6002DR2_API int LMLL_RxFEGetG_LNA_RXFE()
{
	return  getMainModule()->getRxFe()->getG_LNA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the active LNA.
	@param index value index from the list
	- 0 : All LNA's disabled
	- 1 : LNA1 active
	- 2 : LNA2 active
	- 3 : LNA3 active
*/
CTR_6002DR2_API void LMLL_RxFESetLNASEL_RXFE(int index)
{
	getMainModule()->getRxFe()->setLNASEL_RXFE(index);
}

/**
	@ingroup RxFE
	@brief Returns the active LNA.
	@retval 0 : All LNA's disabled
	@retval 1 : LNA1 active
	@retval 2 : LNA2 active
	@retval 3 : LNA3 active
*/
CTR_6002DR2_API int LMLL_RxFEGetLNASEL_RXFE()
{
	return  getMainModule()->getRxFe()->getLNASEL_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the capacitance parallel to the BE of the input NPN transistors.

	To be used at lower frequencies for easier matching. For LNA1 and LNA2 only.
	@param capacitance capacitance to BE (values from 0 to 15)
*/
CTR_6002DR2_API void LMLL_RxFESetCBE_LNA_RXFE(int capacitance)
{
	getMainModule()->getRxFe()->setCBE_LNA_RXFE(capacitance);
}

/**
	@ingroup RxFE
	@brief Returns the capacitance parallel to the BE of the input NPN transistors.
	@return Capacitance to BE
*/
CTR_6002DR2_API int LMLL_RxFEGetCBE_LNA_RXFE()
{
	return  getMainModule()->getRxFe()->getCBE_LNA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets feedback resistor control of the TIA (RXVGA1) to set the mixer gain.
	@param gain Feedback resistor (Gain)
	- if = 120 --> mixer gain = 30 dB (default)
	- if = 102 --> mixer gain = 19 dB
	- if = 2 --> mixer gain = 5 dB
*/
CTR_6002DR2_API void LMLL_RxFESetRFB_TIA_RXFE(int gain)
{
	getMainModule()->getRxFe()->setRFB_TIA_RXFE(gain);
}

/**
	@ingroup RxFE
	@brief Returns feedback resistor control of the TIA (RXVGA1)
	@return Feedback resistor (Gain)
*/
CTR_6002DR2_API int LMLL_RxFEGetRFB_TIA_RXFE()
{
	return  getMainModule()->getRxFe()->getRFB_TIA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets feedback capacitor for the TIA (RXVGA1) to limit the BW.
	@param capacitor Feedback capacitor(BW)
	- if = 0, min cap --> BW~45 MHz for gain of 30 dB (default)
	- if = 19, BW = 2.5 MHz for MixGain = 30 dB at TT.
*/
CTR_6002DR2_API void LMLL_RxFESetCFB_TIA_RXFE(int capacitor)
{
	getMainModule()->getRxFe()->setCFB_TIA_RXFE(capacitor);
}

/**
	@ingroup RxFE
	@brief Returns feedback capacitor for the TIA (RXVGA1).
	@return Feedback capacitor(BW)
*/
CTR_6002DR2_API int LMLL_RxFEGetCFB_TIA_RXFE()
{
	return  getMainModule()->getRxFe()->getCFB_TIA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the on-chip LNA load resistor for the external load mode of the LNA.
	@param gain Exnternal Load(Gain)  values from 0 to 63

	In practice, this will be set to high value, the output will be ac coupled, and the actual load is defined on PCB.
*/
CTR_6002DR2_API void LMLL_RxFESetRDLEXT_LNA_RXFE(int gain)
{
	getMainModule()->getRxFe()->setRDLEXT_LNA_RXFE(gain);
}

/**
	@ingroup RxFE
	@brief Returns the on-chip LNA load resistor for the external load mode of the LNA.
	@return external load(gain)
*/
CTR_6002DR2_API int LMLL_RxFEGetRDLEXT_LNA_RXFE()
{
	return  getMainModule()->getRxFe()->getRDLEXT_LNA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the on-chip LNA load resistor for the internal load mode of the LNA, LNA1 and LNA2.
	@param gain Internal Load(Gain) values from 0 to 63
*/
CTR_6002DR2_API void LMLL_RxFESetRDLINT_LNA_RXFE(int gain)
{
	getMainModule()->getRxFe()->setRDLINT_LNA_RXFE(gain);
}

/**
	@ingroup RxFE
	@brief Returns the on-chip LNA load resistor for the internal load mode of the LNA, LNA1 and LNA2.
	@return Internal Load(Gain)
*/
CTR_6002DR2_API int LMLL_RxFEGetRDLINT_LNA_RXFE()
{
	return  getMainModule()->getRxFe()->getRDLINT_LNA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the bias current for mixer.
	@param bias MIX bias current
	- 0 : 0 bias current
	- 7 : nominal bias current (default)
	- 15 : 2.1 x nominal bias current
*/
CTR_6002DR2_API void LMLL_RxFESetICT_MIX_RXFE(int bias)
{
	getMainModule()->getRxFe()->setICT_MIX_RXFE(bias);
}

/**
	@ingroup RxFE
	@brief Returns the bias current for mixer.
	@return bias MIX bias current
	@retval 0 : 0 bias current
	@retval ...
	@retval 7 : nominal bias current
	@retval ...
	@retval 15 : 2.1 x nominal bias current
*/
CTR_6002DR2_API int LMLL_RxFEGetICT_MIX_RXFE()
{
	return  getMainModule()->getRxFe()->getICT_MIX_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the bias current for LNA.
	@param bias LNA bias current
	- 0 : 0 bias current
	- 7 : nominal bias current (default)
	- 15 : 2.1 x nominal bias current
*/
CTR_6002DR2_API void LMLL_RxFESetICT_LNA_RXFE(int bias)
{
	getMainModule()->getRxFe()->setICT_LNA_RXFE(bias);
}

/**
	@ingroup RxFE
	@brief Returns the bias current for LNA.
	@return LNA bias current
    @retval 0 : 0 bias current
	@retval ...
	@retval 7 : nominal bias current
	@retval ...
	@retval 15 : 2.1 x nominal bias current
*/
CTR_6002DR2_API int LMLL_RxFEGetICT_LNA_RXFE()
{
	return  getMainModule()->getRxFe()->getICT_LNA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the bias current for TIA (RXVGA1).
	@param bias bias current
	- 0 : 0 bias current
	- 7 : nominal bias current (default)
	- 15 : 2.1 x nominal bias current
*/
CTR_6002DR2_API void LMLL_RxFESetICT_TIA_RXFE(int bias)
{
	getMainModule()->getRxFe()->setICT_TIA_RXFE(bias);
}

/**
	@ingroup RxFE
	@brief Returns the bias current for TIA (RXVGA1).
	@retval 0 : 0 bias current
	@retval ...
	@retval 7 : nominal bias current
	@retval ...
	@retval 15 : 2.1 x nominal bias current
*/
CTR_6002DR2_API int LMLL_RxFEGetICT_TIA_RXFE()
{
	return  getMainModule()->getRxFe()->getICT_TIA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets the bias current for mixer LO buffer.
	@param bias MXLOB bias current
	- 0 : 0 bias current
	- 7 : nominal bias current (default)
	- 15 : 2.1 x nominal bias current
*/
CTR_6002DR2_API void LMLL_RxFESetICT_MXLOB_RXFE(int bias)
{
	getMainModule()->getRxFe()->setICT_MXLOB_RXFE(bias);
}

/**
	@ingroup RxFE
	@brief Returns the bias current for mixer LO buffer.
	@return MXLOB bias current
	@retval 0 : 0 bias current
	@retval ...
	@retval 7 : nominal bias current
	@retval ...
	@retval 15 : 2.1 x nominal bias current
*/
CTR_6002DR2_API int LMLL_RxFEGetICT_MXLOB_RXFE()
{
	return  getMainModule()->getRxFe()->getICT_MXLOB_RXFE();
}

/**
	@ingroup RxFE
	@brief Set tweak for the LO bias of the mixer for optimum linearity.
	@param bias LO bias of the MIX values from 0 to 15
*/
CTR_6002DR2_API void LMLL_RxFESetLOBN_MIX_RXFE(int bias)
{
	getMainModule()->getRxFe()->setLOBN_MIX_RXFE(bias);
}

/**
	@ingroup RxFE
	@brief Returns tweak for the LO bias of the mixer.
	@return LO bias of the MIX
*/
CTR_6002DR2_API int LMLL_RxFEGetLOBN_MIX_RXFE()
{
	return  getMainModule()->getRxFe()->getLOBN_MIX_RXFE();
}

/**
	@ingroup RxFE
	@brief Enables or disables TIA (RXVGA1).
	@param state TIA enabled
	- 0 : block inactive
	- 1 : block active (default)
*/
CTR_6002DR2_API void LMLL_RxFESetPD_TIA_RXFE(bool state)
{
	getMainModule()->getRxFe()->setPD_TIA_RXFE(state);
}

/**
	@ingroup RxFE
	@brief Returns whether TIA (RXVGA1) is enabled or disabled.
	@return is TIA enabled
	@retval 0 : block inactive
	@retval 1 : block active
*/
CTR_6002DR2_API bool LMLL_RxFEGetPD_TIA_RXFE()
{
	return  getMainModule()->getRxFe()->getPD_TIA_RXFE();
}

/**
	@ingroup RxFE
	@brief Enables or disables mixer LO buffer.
	@param state MXLOB enabled
	- 0 : block inactive
	- 1 : block active
*/
CTR_6002DR2_API void LMLL_RxFESetPD_MXLOB_RXFE(bool state)
{
	getMainModule()->getRxFe()->setPD_MXLOB_RXFE(state);
}

/**
	@ingroup RxFE
	@brief Returns whether mixer LO buffer is enabled or disabled.
	@return is MXLOB enabled
	@retval 0 : block inactive
	@retval 1 : block active
*/
CTR_6002DR2_API bool LMLL_RxFEGetPD_MXLOB_RXFE()
{
	return  getMainModule()->getRxFe()->getPD_MXLOB_RXFE();
}

/**
	@ingroup RxFE
	@brief Enables or disables mixer.
	@param state mixer enabled
	- 0 : block inactive
	- 1 : block active
*/
CTR_6002DR2_API void LMLL_RxFESetPD_MIX_RXFE(bool state)
{
	getMainModule()->getRxFe()->setPD_MIX_RXFE(state);
}

/**
	@ingroup RxFE
	@brief Returns whether mixer is enabled or disabled.
	@return is mixer enabled
	@retval 0 : block inactive
	@retval 1 : block active
*/
CTR_6002DR2_API bool LMLL_RxFEGetPD_MIX_RXFE()
{
	return  getMainModule()->getRxFe()->getPD_MIX_RXFE();
}

/**
	@ingroup RxFE
	@brief Enables or disables LNA.
	@param state LNA enabled
	- 0 : block inactive
	- 1 : block active
*/
CTR_6002DR2_API void LMLL_RxFESetPD_LNA_RXFE(bool state)
{
	getMainModule()->getRxFe()->setPD_LNA_RXFE(state);
}

/**
	@ingroup RxFE
	@brief Returns whether LNA is enabled or disabled.
	@return is LNA enabled
	@retval 0 : block inactive
	@retval 1 : block active
*/
CTR_6002DR2_API bool LMLL_RxFEGetPD_LNA_RXFE()
{
	return  getMainModule()->getRxFe()->getPD_LNA_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets termination resistor on external mixer input enable.
	@param state resistor state
	- 0 : Inactive (default)
	- 1 : Active
*/
CTR_6002DR2_API void LMLL_RxFESetRINEN_MIX_RXFE(bool state)
{
	getMainModule()->getRxFe()->setRINEN_MIX_RXFE(state);
}

/**
	@ingroup RxFE
	@brief Returns termination resistor on external mixer input enable.
	@retval 0 : Inactive
	@retval 1 : Active
*/
CTR_6002DR2_API bool LMLL_RxFEGetRINEN_MIX_RXFE()
{
	return  getMainModule()->getRxFe()->getRINEN_MIX_RXFE();
}

/**
	@ingroup RxFE
	@brief Sets LNA3 fine gain adjustment.
	@param gain LNA 3 fine gain
	- 0 : +0 dB (default)
	- 1 : +1 dB
	- 2 : +2 dB
	- 3 : +3 dB
*/
CTR_6002DR2_API void LMLL_RxFESetG_FINE_LNA3_RXFE(int gain)
{
	getMainModule()->getRxFe()->setG_FINE_LNA3_RXFE(gain);
}

/**
	@ingroup RxFE
	@brief Returns LNA3 fine gain adjustment.
	@retval 0 : +0 dB (default)
	@retval 1 : +1 dB
	@retval 2 : +2 dB
	@retval 3 : +3 dB
*/
CTR_6002DR2_API int LMLL_RxFEGetG_FINE_LNA3_RXFE()
{
	return  getMainModule()->getRxFe()->getG_FINE_LNA3_RXFE();
}


//==============================================================================
// End of RxFE Module

// ADDC Module
// =============================================================================
/**
	@ingroup ADDC
	@brief Sets Rx Fsync polarity, frame start
	@param polarity
	- 1 : 1
	- 0 : 0 (default)
*/
CTR_6002DR2_API void LMLL_ADDCSetRX_FSYNC_P(int polarity)
{
	getMainModule()->getADDC()->setRX_FSYNC_P(polarity);
	getMainModule()->getTesting()->m_frameStart = polarity;
}

/**
	@ingroup ADDC
	@brief Returns Rx Fsync polarity, frame start
	@return polarity
	@retval 1 : 1
	@retval 0 : 0
*/
CTR_6002DR2_API int LMLL_ADDCGetRX_FSYNC_P()
{
	return  getMainModule()->getADDC()->getRX_FSYNC_P();
}

/**
	@ingroup ADDC
	@brief Sets Rx interleave Mode.
	@param mode interleave
	- 0 : I,Q
	- 1 : Q,I
*/
CTR_6002DR2_API void LMLL_ADDCSetRX_INTER(int mode)
{
	getMainModule()->getADDC()->setRX_INTER(mode);
	getMainModule()->getTesting()->m_swapIQ = mode;
}

/**
	@ingroup ADDC
	@brief Returns Rx interleave Mode.
	@return interleave mode
	@retval 0 : I,Q
	@retval 1 : Q,I
*/
CTR_6002DR2_API int LMLL_ADDCGetRX_INTER()
{
	return  getMainModule()->getADDC()->getRX_INTER();
}

/**
	@ingroup ADDC
	@brief Sets DAC clock edge polarity.
	@param polarity
	- 0 : positive
	- 1 : negative (default)
*/
CTR_6002DR2_API void LMLL_ADDCSetDAC_CLK_P(int polarity)
{
	getMainModule()->getADDC()->setDAC_CLK_P(polarity);
}

/**
	@ingroup ADDC
	@brief Returns DAC clock edge polarity.
	@return polarity
	@retval 0 : positive
	@retval 1 : negative
*/
CTR_6002DR2_API int LMLL_ADDCGetDAC_CLK_P()
{
	return  getMainModule()->getADDC()->getDAC_CLK_P();
}

/**
	@ingroup ADDC
	@brief Sets Tx Fsync polarity, frame start.
	@param polarity
	- 1 : 1
	- 0 : 0 (default)
*/
CTR_6002DR2_API void LMLL_ADDCSetTX_FSYNC_P(int polarity)
{
	getMainModule()->getADDC()->setTX_FSYNC_P(polarity);
}

/**
	@ingroup ADDC
	@brief Returns Tx Fsync polarity, frame start.
	@return polarity
	- 1 : 1
	- 0 : 0
*/
CTR_6002DR2_API int LMLL_ADDCGetTX_FSYNC_P()
{
	return  getMainModule()->getADDC()->getTX_FSYNC_P();
}

/**
	@ingroup ADDC
	@brief Sets Tx interleave mode.
	@param mode interleave mode
	- 0 : I,Q
	- 1 : Q,I
*/
CTR_6002DR2_API void LMLL_ADDCSetTX_INTER(int mode)
{
	getMainModule()->getADDC()->setTX_INTER(mode);
}

/**
	@ingroup ADDC
	@brief Returns Tx interleave mode.
	@return interleave mode
	@retval 0 : I,Q
	@retval 1 : Q,I
*/
CTR_6002DR2_API int LMLL_ADDCGetTX_INTER()
{
	return  getMainModule()->getADDC()->getTX_INTER();
}

/**
	@ingroup ADDC
	@brief Enables or disables DAC.
	@param state DAC enabled
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API void LMLL_ADDCSetEN_DAC(bool state)
{
	getMainModule()->getADDC()->setEN_DAC(state);
}

/**
	@ingroup ADDC
	@brief Returns whether DAC is enabled or disabled.
	@return is DAC enabled
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API bool LMLL_ADDCGetEN_DAC()
{
	return  getMainModule()->getADDC()->getEN_DAC();
}

/**
	@ingroup ADDC
	@brief Enables or disables ADDC.
	@param state ADDC enabled
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API void LMLL_ADDCSetEN_ADC_DAC(bool state)
{
	getMainModule()->getADDC()->setEN_ADC_DAC(state);
}

/**
	@ingroup ADDC
	@brief Returns whether ADDC is enabled or disabled.
	@return is ADDC enabled
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_ADDCGetEN_ADC_DAC()
{
	return  getMainModule()->getADDC()->getEN_ADC_DAC();
}


/**
	@ingroup ADDC
	@brief Enables or disables ADC(I).
	@param state ADC(I) enabled
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API void LMLL_ADDCSetEN_ADC_I(bool state)
{
	getMainModule()->getADDC()->setEN_ADC_I(state);
}

/**
	@ingroup ADDC
	@brief Returns whether ADC(I) is enabled or disabled.
	@return is ADC(I) enabled
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_ADDCGetEN_ADC_I()
{
	return  getMainModule()->getADDC()->getEN_ADC_I();
}

/**
	@ingroup ADDC
	@brief Enables or disables ADC(Q).
	@param state ADC(Q) enabled
	- 0 : disabled
	- 1 : enabled
*/
CTR_6002DR2_API void LMLL_ADDCSetEN_ADC_Q(bool state)
{
	getMainModule()->getADDC()->setEN_ADC_Q(state);
}

/**
	@ingroup ADDC
	@brief Returns whether ADC(Q) is enabled or disabled.
	@return is ADC(Q) enabled
	@retval 0 : disabled
	@retval 1 : enabled
*/
CTR_6002DR2_API bool LMLL_ADDCGetEN_ADC_Q()
{
	return  getMainModule()->getADDC()->getEN_ADC_Q();
}

/**
	@ingroup ADDC
	@brief Enables or disables ADC reference.
	@param state ADC reference enabled
	- 0 : off
	- 1 : enabled (default)
*/
CTR_6002DR2_API void LMLL_ADDCSetEN_ADC_REF(bool state)
{
	getMainModule()->getADDC()->setEN_ADC_REF(state);
}

/**
	@ingroup ADDC
	@brief Returns whether ADC reference is enabled.
	@return is ADC reference enabled
	@retval 0 : off
	@retval 1 : enabled (default)
*/
CTR_6002DR2_API bool LMLL_ADDCGetEN_ADC_REF()
{
	return  getMainModule()->getADDC()->getEN_ADC_REF();
}

/**
	@ingroup ADDC
	@brief Enables or disables master reference.
	@param state master reference enabled
	- 0 : off
	- 1 : enabled (default)
*/
CTR_6002DR2_API void LMLL_ADDCSetEN_M_REF(bool state)
{
	getMainModule()->getADDC()->setEN_M_REF(state);
}

/**
	@ingroup ADDC
	@brief Returns whether master reference is enabled.
	@return is master reference enabled
	@retval 0 : off
	@retval 1 : enabled (default)
*/
CTR_6002DR2_API bool LMLL_ADDCGetEN_M_REF()
{
	return  getMainModule()->getADDC()->getEN_M_REF();
}

/**
	@ingroup ADDC
	@brief Sets bandgap temperature coefficient.
	@param index value index from the list
	- 0 : -8 (min)
	- 1 : -7
	- ...
	- 8 : 0 (nominal)
	- ...
	- 15 : 7 (max)
*/
CTR_6002DR2_API void LMLL_ADDCSetBandgapTemp(int index)
{
	getMainModule()->getADDC()->setBandgapTemp(index);
}

/**
	@ingroup ADDC
	@brief Returns bandgap temperature coefficient.
	@retval 0 : -8 (min)
	@retval 1 : -7
	@retval ...
	@retval 8 : 0 (nominal)
	@retval ...
	@retval 15 : 7 (max)
*/
CTR_6002DR2_API int LMLL_ADDCGetBandgapTemp()
{
	return  getMainModule()->getADDC()->getBandgapTemp();
}

/**
	@ingroup ADDC
	@brief Sets bandgap gain.
	@param index value index from the list
	- 0 : -8 (min)
	- 1 : -7
	- ...
	- 8 : 0 (nominal)
	- ...
	- 15 : 7 (max)
*/
CTR_6002DR2_API void LMLL_ADDCSetBandgapGain(int index)
{
	getMainModule()->getADDC()->setBandgapGain(index);
}

/**
	@ingroup ADDC
	@brief Returns bandgap gain.
	@retval 0 : -8 (min)
	@retval 1 : -7
	@retval ...
	@retval 8 : 0 (nominal)
	@retval ...
	@retval 15 : 7 (max)
*/
CTR_6002DR2_API int LMLL_ADDCGetBandgapGain()
{
	return  getMainModule()->getADDC()->getBandgapGain();
}

/**
	@ingroup ADDC
	@brief Sets reference Amps bias adjust.
	@param index value index from the list
	- 0 : 20 uA
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetRefAmpsBiasAdj(int index)
{
	getMainModule()->getADDC()->setRefAmpsBiasAdj(index);
}

/**
	@ingroup ADDC
	@brief Returns reference Amps bias adjust.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetRefAmpsBiasAdj()
{
	return  getMainModule()->getADDC()->getRefAmpsBiasAdj();
}

/**
	@ingroup ADDC
	@brief Sets reference Amps bias UP.
	@param index value index from the list
	- 0 : 1.0X
	- 1 : 1.5X
	- 2 : 2.0X
	- 3 : 2.5X
*/
CTR_6002DR2_API void LMLL_ADDCSetRefAmpsBiasUp(int index)
{
	getMainModule()->getADDC()->setRefAmpsBiasUp(index);
}

/**
	@ingroup ADDC
	@brief Returns reference Amps bias UP.
	@retval 0 : 1.0X
	@retval 1 : 1.5X
	@retval 2 : 2.0X
	@retval 3 : 2.5X
*/
CTR_6002DR2_API int LMLL_ADDCGetRefAmpsBiasUp()
{
	return  getMainModule()->getADDC()->getRefAmpsBiasUp();
}

/**
	@ingroup ADDC
	@brief Sets reference Amps bias DOWN.
	@param bias Amps bias DOWN values from 0 to 15
*/
CTR_6002DR2_API void LMLL_ADDCSetRefAmpsBiasDn(int bias)
{
	getMainModule()->getADDC()->setRefAmpsBiasDn(bias);
}

/**
	@ingroup ADDC
	@brief Returns reference Amps bias DOWN.
	@return Amps bias DOWN
*/
CTR_6002DR2_API int LMLL_ADDCGetRefAmpsBiasDn()
{
	return  getMainModule()->getADDC()->getRefAmpsBiasDn();
}

/**
	@ingroup ADDC
	@brief Sets reference bias resistor adjust.
	@param index value index from the list
	- 0 : 20 uA (default)
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetRefResistorBiasAdj(int index)
{
	getMainModule()->getADDC()->setRefResistorBiasAdj(index);
}

/**
	@ingroup ADDC
	@brief Returns reference bias resistor adjust.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetRefResistorBiasAdj()
{
	return  getMainModule()->getADDC()->getRefResistorBiasAdj();
}

/**
	@ingroup ADDC
	@brief Sets reference bias UP.
	@param index value index from the list
	- 0 : 1.0X (default)
	- 1 : 1.5X
	- 2 : 2.0X
	- 3 : 2.5X
*/
CTR_6002DR2_API void LMLL_ADDCSetRefBiasUp(int index)
{
	getMainModule()->getADDC()->setRefBiasUp(index);
}

/**
	@ingroup ADDC
	@brief Returns reference bias UP.
	@retval 0 : 1.0X (default)
	@retval 1 : 1.5X
	@retval 2 : 2.0X
	@retval 3 : 2.5X
*/
CTR_6002DR2_API int LMLL_ADDCGetRefBiasUp()
{
	return  getMainModule()->getADDC()->getRefBiasUp();
}

/**
	@ingroup ADDC
	@brief Sets reference bias DOWN.
	@param bias reference bias DOWN values from 0 to 15
*/
CTR_6002DR2_API void LMLL_ADDCSetRefBiasDn(int bias)
{
	getMainModule()->getADDC()->setRefBiasDn(bias);
}

/**
	@ingroup ADDC
	@brief Returns reference bias DOWN.
	@return reference bias DOWN
*/
CTR_6002DR2_API int LMLL_ADDCGetRefBiasDn()
{
	return  getMainModule()->getADDC()->getRefBiasDn();
}

/**
	@ingroup ADDC
	@brief Sets Reference gain adjust.
	@param index value index from the list
	- 0 : 1.50V
	- 1 : 1.75V
	- 2 : 1.00V
	- 3 : 1.25V
*/
CTR_6002DR2_API void LMLL_ADDCSetRefGainAdj(int index)
{
	getMainModule()->getADDC()->setRefGainAdj(index);
}

/**
	@ingroup ADDC
	@brief Returns Reference gain adjust.
	@retval 0 : 1.50V
	@retval 1 : 1.75V
	@retval 2 : 1.00V
	@retval 3 : 1.25V
*/
CTR_6002DR2_API int LMLL_ADDCGetRefGainAdj()
{
	return  getMainModule()->getADDC()->getRefGainAdj();
}

/**
	@ingroup ADDC
	@brief Sets common mode adjust.
	@param index value index from the list
	- 0 : 875mV
	- 1 : 960mV
	- 2 : 700mV
	- 3 : 790mV
*/
CTR_6002DR2_API void LMLL_ADDCSetCoomonModeAdj(int index)
{
	getMainModule()->getADDC()->setCoomonModeAdj(index);
}

/**
	@ingroup ADDC
	@brief Returns common mode adjust.
	@retval 0 : 875mV
	@retval 1 : 960mV
	@retval 2 : 700mV
	@retval 3 : 790mV
*/
CTR_6002DR2_API int LMLL_ADDCGetCoomonModeAdj()
{
	return  getMainModule()->getADDC()->getCoomonModeAdj();
}

/**
	@ingroup ADDC
	@brief Sets reference buffer boost.
	@param index value index from the list
	- 0 : 1.0X
	- 1 : 1.5X
	- 2 : 2.0X
	- 3 : 2.5X
*/
CTR_6002DR2_API void LMLL_ADDCSetRefBufferBoost(int index)
{
	getMainModule()->getADDC()->setRefBufferBoost(index);
}

/**
	@ingroup ADDC
	@brief Returns reference buffer boost.
	@retval 0 : 1.0X
	@retval 1 : 1.5X
	@retval 2 : 2.0X
	@retval 3 : 2.5X
*/
CTR_6002DR2_API int LMLL_ADDCGetRefBufferBoost()
{
	return  getMainModule()->getADDC()->getRefBufferBoost();
}

/**
	@ingroup ADDC
	@brief Enables or disables ADC input buffer.
	@param state ADC input buffer disabled
	- 1 : Disabled (default)
	- 0 : Enabled
*/
CTR_6002DR2_API void LMLL_ADDCSetInputBufferDisable(bool state)
{
	getMainModule()->getADDC()->setInputBufferDisable(state);
}

/**
	@ingroup ADDC
	@brief Returns whether ADC input buffer is disabled.
	@return ADC input buffer disabled
	- 1 : Disabled
	- 0 : Enabled
*/
CTR_6002DR2_API bool LMLL_ADDCGetInputBufferDisable()
{
	return  getMainModule()->getADDC()->getInputBufferDisable();
}

/**
	@ingroup ADDC
	@brief Sets ADC sampling phase.
	@param phase sampling phase
	- 0 : rising edge (default)
	- 1 : falling edge
*/
CTR_6002DR2_API void LMLL_ADDCSetADCSamplingPhase(int phase)
{
	getMainModule()->getADDC()->setADCSamplingPhase(phase);
}

/**
	@ingroup ADDC
	@brief Returns ADC sampling phase.
	@retval 0 : rising edge (default)
	@retval 1 : falling edge
*/
CTR_6002DR2_API int LMLL_ADDCGetADCSamplingPhase()
{
	return  getMainModule()->getADDC()->getADCSamplingPhase();
}

/**
	@ingroup ADDC
	@brief Sets clock non-overlap adjust.
	@param index value index from the list
	- 0 : Nominal (default)
	- 1 : +450ps
	- 2 : +150ps
	- 3 : +300ps
*/
CTR_6002DR2_API void LMLL_ADDCSetClockNonOverlapAdjust(int index)
{
	getMainModule()->getADDC()->setClockNonOverlapAdjust(index);
}

/**
	@ingroup ADDC
	@brief Returns clock non-overlap adjust.
	@retval 0 : Nominal (default)
	@retval 1 : +450ps
	@retval 2 : +150ps
	@retval 3 : +300ps
*/
CTR_6002DR2_API int LMLL_ADDCGetClockNonOverlapAdjust()
{
	return  getMainModule()->getADDC()->getClockNonOverlapAdjust();
}

/**
	@ingroup ADDC
	@brief Sets ADC bias resistor adjust.
	@param index value index from the list
	- 0 : 20 uA (default)
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetADCBiasResistorAdjust(int index)
{
	getMainModule()->getADDC()->setADCBiasResistorAdjust(index);
}

/**
	@ingroup ADDC
	@brief Returns ADC bias resistor adjust.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetADCBiasResistorAdjust()
{
	return  getMainModule()->getADDC()->getADCBiasResistorAdjust();
}

/**
	@ingroup ADDC
	@brief Sets main bias DOWN.
	@param index value index from the list
	- 0 : Nominal
	- ...
	- 3 : Min Bias
*/
CTR_6002DR2_API void LMLL_ADDCSetMainBiasDN(int index)
{
	getMainModule()->getADDC()->setMainBiasDN(index);
}

/**
	@ingroup ADDC
	@brief Returns main bias DOWN.
	@retval 0 : Nominal
	@retval ...
	@retval 3 : Min Bias
*/
CTR_6002DR2_API int LMLL_ADDCGetMainBiasDN()
{
	return  getMainModule()->getADDC()->getMainBiasDN();
}

/**
	@ingroup ADDC
	@brief Sets ADC Amp1 stage1 bias UP.
	@param index value index from the list
	- 0 : 20 uA (default)
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetADCAmp1Stage1BiasUp(int index)
{
	getMainModule()->getADDC()->setADCAmp1Stage1BiasUp(index);
}

/**
	@ingroup ADDC
	@brief Returns ADC Amp1 stage1 bias UP.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetADCAmp1Stage1BiasUp()
{
	return  getMainModule()->getADDC()->getADCAmp1Stage1BiasUp();
}

/**
	@ingroup ADDC
	@brief Sets ADC Amp2-4 stage1 bias UP.
	@param index value index from the list
	- 0 : 20 uA (default)
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetADCAmp24Stage1BiasUp(int index)
{
	getMainModule()->getADDC()->setADCAmp24Stage1BiasUp(index);
}

/**
	@ingroup ADDC
	@brief Returns ADC Amp2-4 stage1 bias UP.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetADCAmp24Stage1BiasUp()
{
	return  getMainModule()->getADDC()->getADCAmp24Stage1BiasUp();
}

/**
	@ingroup ADDC
	@brief Sets ADC Amp1 stage2 bias UP.
	@param index value index from the list
	- 0 : 20 uA (default)
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetADCAmp1Stage2BiasUp(int index)
{
	getMainModule()->getADDC()->setADCAmp1Stage2BiasUp(index);
}

/**
	@ingroup ADDC
	@brief Returns ADC Amp1 stage2 bias UP.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetADCAmp1Stage2BiasUp()
{
	return  getMainModule()->getADDC()->getADCAmp1Stage2BiasUp();
}

/**
	@ingroup ADDC
	@brief Sets ADC Amp2-4 stage2 bias UP.
	@param index value index from the list
	- 0 : 20 uA (default)
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetADCAmp24Stage2BiasUp(int index)
{
	getMainModule()->getADDC()->setADCAmp24Stage2BiasUp(index);
}

/**
	@ingroup ADDC
	@brief Returns ADC Amp2-4 stage2 bias UP.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetADCAmp24Stage2BiasUp()
{
	return  getMainModule()->getADDC()->getADCAmp24Stage2BiasUp();
}

/**
	@ingroup ADDC
	@brief Sets quantizer bias UP.
	@param index value index from the list
	- 0 : 20 uA (default)
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetQuantizerBiasUp(int index)
{
	getMainModule()->getADDC()->setQuantizerBiasUp(index);
}

/**
	@ingroup ADDC
	@brief Returns quantizer bias UP.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetQuantizerBiasUp()
{
	return  getMainModule()->getADDC()->getQuantizerBiasUp();
}

/**
	@ingroup ADDC
	@brief Sets input buffer bias UP.
	@param index value index from the list
	- 0 : 20 uA (default)
	- 1 : 40 uA
	- 2 : 10 uA
	- 3 : 15 uA
*/
CTR_6002DR2_API void LMLL_ADDCSetInputBufferBiasUp(int index)
{
	getMainModule()->getADDC()->setInputBufferBiasUp(index);
}

/**
	@ingroup ADDC
	@brief Returns input buffer bias UP.
	@retval 0 : 20 uA
	@retval 1 : 40 uA
	@retval 2 : 10 uA
	@retval 3 : 15 uA
*/
CTR_6002DR2_API int LMLL_ADDCGetInputBufferBiasUp()
{
	return  getMainModule()->getADDC()->getInputBufferBiasUp();
}

/**
	@ingroup ADDC
	@brief Sets DAC internal output load resistor.
	@param index value index from the list
	- 0 : Open circuit
	- 1 : 100 Ohms
	- 2 : 200 Ohms(default)
	- 3 : 66 Ohms
	- 4 : 200 Ohms
	- 5 : 66 Ohms
	- 6 : 100 Ohms
	- 7 : 50 Ohms
*/
CTR_6002DR2_API void LMLL_ADDCSetDACInternalOutputLoadResistor(int index)
{
	getMainModule()->getADDC()->setDACInternalOutputLoadResistor(index);
}

/**
	@ingroup ADDC
	@brief Returns DAC internal output load resistor.
	@retval 0 : Open circuit
	@retval 1 : 100 Ohms
	@retval 2 : 200 Ohms(default)
	@retval 3 : 66 Ohms
	@retval 4 : 200 Ohms
	@retval 5 : 66 Ohms
	@retval 6 : 100 Ohms
	@retval 7 : 50 Ohms
*/
CTR_6002DR2_API int LMLL_ADDCGetDACInternalOutputLoadResistor()
{
	return  getMainModule()->getADDC()->getDACInternalOutputLoadResistor();
}

/**
	@ingroup ADDC
	@brief Sets DAC reference current resistor.
	@param index value index from the list
	- 0 : Internal
	- 1 : External (default)
*/
CTR_6002DR2_API void LMLL_ADDCSetDACReferenceCurrentResistor(int index)
{
	getMainModule()->getADDC()->setDACReferenceCurrentResistor(index);
}

/**
	@ingroup ADDC
	@brief Returns DAC reference current resistor.
	@retval 0 : Internal
	@retval 1 : External
*/
CTR_6002DR2_API int LMLL_ADDCGetDACReferenceCurrentResistor()
{
	return  getMainModule()->getADDC()->getDACReferenceCurrentResistor();
}

/**
	@ingroup ADDC
	@brief Sets DAC full scale output current (single-ended).
	@param index value index from the list
	- 0 : lout FS = 5mA
	- 1 : lout FS = 10mA
	- 2 : lout FS = 2.5mA
	- 3 : lout FS = 5mA
*/
CTR_6002DR2_API void LMLL_ADDCSetDACFullScaleOutputCurrent(int index)
{
	getMainModule()->getADDC()->setDACFullScaleOutputCurrent(index);
}

/**
	@ingroup ADDC
	@brief Returns DAC full scale output current.
	@retval 0 : lout FS = 5mA
	@retval 1 : lout FS = 10mA
	@retval 2 : lout FS = 2.5mA
	@retval 3 : lout FS = 5mA
*/
CTR_6002DR2_API int LMLL_ADDCGetDACFullScaleOutputCurrent()
{
	return  getMainModule()->getADDC()->getDACFullScaleOutputCurrent();
}

/**
	@ingroup ADDC
	@brief Sets ADDC decode mode.
	@param mode decode mode
	- 0 : decode control signals
	- 1 : use control signals from test mode registers.
*/
CTR_6002DR2_API void LMLL_ADDCSetDecode(int mode)
{
	getMainModule()->getADDC()->setDecode(mode);
}

/**
	@ingroup ADDC
	@brief Returns ADDC decode mode.
	@retval 0 : decode control signals
	@retval 1 : use control signals from test mode registers.
*/
CTR_6002DR2_API int LMLL_ADDCGetDecode()
{
	return  getMainModule()->getADDC()->getDecode();
}
// =============================================================================
// End of ADDC Module

// FreqVsCap
// =============================================================================
CTR_6002DR2_API void LMLL_FreqVsCapSetVco(sVcoVsCap *sVco, int number, bool TxPLL)
{
	TxPLL_Module *pll;
	if(TxPLL)
		pll = getMainModule()->getTxPLL();
	else
		pll = getMainModule()->getRxPLL();

	switch(number)
	{
	case 1:
		pll->m_FreqVsCap->setVco1(sVco);
		break;
	case 2:
		pll->m_FreqVsCap->setVco2(sVco);
		break;
	case 3:
		pll->m_FreqVsCap->setVco3(sVco);
		break;
	case 4:
		pll->m_FreqVsCap->setVco4(sVco);
		break;
	}
}
CTR_6002DR2_API sVcoVsCap *LMLL_FreqVsCapGetVco(int number, bool TxPLL)
{
	TxPLL_Module *pll;
	if(TxPLL)
		pll = getMainModule()->getTxPLL();
	else
		pll = getMainModule()->getRxPLL();

	switch(number)
	{
	case 1:
		return pll->m_FreqVsCap->getVco1();
	case 2:
		return pll->m_FreqVsCap->getVco2();
	case 3:
		return pll->m_FreqVsCap->getVco3();
	case 4:
		return pll->m_FreqVsCap->getVco4();
	}
	return NULL;
}
// =============================================================================
// End of FreqVsCap

// Board2
//==============================================================================
/**
	@ingroup Board
	@brief Loads register map from file
	@param *FName filename or full path to file
	@retval false failed
	@retval true succeeded
*/
CTR_6002DR2_API bool LMLL_BoardLoadRegValuesFromFile(char *FName)
{
	return  getMainModule()->getBoard2()->LoadRegValuesFromFile(FName);
}
/**
	@ingroup Board
	@brief Configures Si5356A using currently loaded register map.
*/
CTR_6002DR2_API void LMLL_BoardConfigureSi5356A()
{
	getMainModule()->getBoard2()->ConfigureSi5356A();
}

/**
    @ingroup Board
    @brief Sets selected clock to desired frequency
    @param clkID clock number 0-0/1 1-2/3 2-4/5 3-6/7
    @param refClkMHz reference clock in MHz.
    @param ClockMHz new clock frequency in MHz.
*/
CTR_6002DR2_API void LMLL_BoardSetFrequency(unsigned int clkID, float refClkMHz, float ClockMHz)
{
    getMainModule()->getBoard2()->SetFrequency(clkID, refClkMHz, ClockMHz);
}

/**
    @ingroup Board
    @brief Sets selected clock signal inversion
    @param clkID clock number 0-0/1 1-2/3 2-4/5 3-6/7
    @param inversion
        - No inversion
        - 1 invert even clock
        - 2 invert odd clock
        - 3 invert both clocks
*/
CTR_6002DR2_API void LMLL_BoardSetClockInversion(unsigned int clkID, unsigned int inversion)
{
    getMainModule()->getBoard2()->SetInvertClock(clkID, inversion);
}

/**
    @ingroup Board
    @brief Sets selected clock output format
    @param clkID clock number 0-0/1 1-2/3 2-4/5 3-6/7
    @param format
        - 1 Even clock = on, Odd clock = off
        - 2 Even clock = off, Odd clock = on
        - 3 Even clock = on, Odd clock = on
*/
CTR_6002DR2_API void LMLL_BoardSetClockOutputFormat(unsigned int clkID, unsigned int format)
{
    getMainModule()->getBoard2()->SetOutputFormat(clkID, format);
}

/**
    @ingroup Board
    @brief Enables or disables selected clock
    @param clkID clock number 0-0/1 1-2/3 2-4/5 3-6/7
    @param clock_enabled set true to enabled clock.
*/
CTR_6002DR2_API void LMLL_BoardEnableClock(unsigned int clkID, bool clock_enabled)
{
    getMainModule()->getBoard2()->EnableClock(clkID, clock_enabled);
    getMainModule()->getBoard2()->PowerUpClock(clkID, clock_enabled);
}

/**
    @ingroup Board
    @brief Selects reference clock input
    @param CLKIN
        - false : xoclk
        - true : CLKIN
*/
CTR_6002DR2_API void LMLL_BoardSelectReferenceClk(bool CLKIN)
{
    getMainModule()->getBoard2()->SetRefClockInput(CLKIN);
}

/**
    @ingroup Board
    @brief Selects crystal frequency
    @param freqID
        - 0: 25 MHz
        - 1: 27 MHz
*/
CTR_6002DR2_API void LMLL_BoardSelectCrystalFrequency(unsigned int freqID)
{
    getMainModule()->getBoard2()->SetCrystalFreq(freqID);
}
//==============================================================================
// End of Board2


//==============================================================================
// Connection to chip interface
//==============================================================================

/**
    @ingroup ConnectionManager
    @brief Function to handle device changing
    This function should be called when device connection or disconnection is detected
*/
CTR_6002DR2_API int LMAL_SerialPortOnDeviceChange()
{
    getMainModule()->getSerPort()->DevicesChanged();
}

/**
	@ingroup ConnectionManager
	@brief Initializes variables and opens first found chip.
	@retval 0 - failed
	@retval 1 - succeeded
*/
CTR_6002DR2_API int LMAL_SerialPortInitialize()
{
	getMainModule()->getSerPort()->Initialize();
	return  1;
}

/**
	@ingroup ConnectionManager
	@brief Checks all available connections and connects to first found chip.
	@retval 0 - chip not found
	@retval 1 - chip connection opened
*/
CTR_6002DR2_API int LMAL_Open()
{
	int opened = getMainModule()->getSerPort()->Open();
	if(opened)
		getMainModule()->UpdateVerRevMask();
	return opened;
}

/**
	@ingroup ConnectionManager
	@brief Opens i-th device from available device list.
	@param i device index.
	@retval 0 - chip not found
	@retval 1 - chip connection opened
*/
CTR_6002DR2_API int LMAL_OpenI(unsigned int i)
{
	int opened = getMainModule()->getSerPort()->Open(i);
	if(opened)
		getMainModule()->UpdateVerRevMask();
	return opened;
}

/**
	@ingroup ConnectionManager
	@brief Closes connection to chip.
*/
CTR_6002DR2_API int LMAL_Close()
{
	return  getMainModule()->getSerPort()->Close();
}

/**
	@ingroup ConnectionManager
	@brief Checks if connection is open.
	@retval false connection to chip is closed
	@retval true connection to chip is open
*/
CTR_6002DR2_API bool LMAL_IsOpen()
{
	return  getMainModule()->getSerPort()->IsOpen();
}

/**
	@ingroup ConnectionManager
	@brief Selects which connection type to use: -1 - undefined, 0 - COM, 1 - USB
	@param Type connection type
	@retval 0 operation failed
	@retval 1 operation succeeded
*/
CTR_6002DR2_API int LMAL_SetConnectionType(int Type)
{
	 return getMainModule()->getSerPort()->SetConnectionType(static_cast<enumPortType>(Type));
}

/**
	@ingroup ConnectionManager
	@brief Activates and deactivates reset signal in the chip.
*/
CTR_6002DR2_API void LMAL_SPI_Rst()
{
	getMainModule()->getSerPort()->SPI_Rst();
}

/**
	@ingroup ConnectionManager
	@brief Activates reset signal in the chip.
*/
CTR_6002DR2_API void LMAL_SPI_RstAct()
{
	getMainModule()->getSerPort()->SPI_RstAct();
}

/**
	@ingroup ConnectionManager
	@brief Deactivates reset signal in the chip.
*/
CTR_6002DR2_API void LMAL_SPI_RstInact()
{
	getMainModule()->getSerPort()->SPI_RstInact();
}

/**
	@ingroup ConnectionManager
	@brief Reads one byte from the chip.
	@param Command address to read
	@return received value
*/
CTR_6002DR2_API char LMAL_SPI_Read_OneByte(char Command)
{
	return  getMainModule()->getSerPort()->SPI_Read_OneByte(Command);
}

/**
	@ingroup ConnectionManager
	@brief Writes given buffer to chip.
	@param buffer containing address and data pairs.
	@param length number of bytes in buffer.
	@retval false failed
	@retval true succeeded
*/
CTR_6002DR2_API bool LMAL_SendData(const unsigned char *buffer, int &length)
{
	return  getMainModule()->getSerPort()->SendData(buffer, length);
}

/**
	@ingroup ConnectionManager
	@brief Reads data from the chip.
	@param readCommands buffer that will be sent to the chip, it should contain addresses that needs to be read
	@param cmdCount number of reading commands
	@param destBuffer buffer to store received data, must be big enough to store all received data
	@param &bytesRead number of bytes received from chip
	@retval false failed
	@retval true succeeded
*/
CTR_6002DR2_API bool LMAL_ReadData(unsigned char *readCommands, int cmdCount, unsigned char *destBuffer, int &bytesRead)
{
	return  getMainModule()->getSerPort()->ReadData(readCommands, cmdCount, destBuffer, bytesRead);
}

/**
	@ingroup ConnectionManager
	@brief Returns currently used connection type
	@retval -1 undefined
	@retval 0 com port
	@retval 1 usb port
*/
CTR_6002DR2_API int LMAL_GetConnectionType()
{
	return  getMainModule()->getSerPort()->GetConnectionType();
}

/**
	@ingroup ConnectionManager
	@brief Returns currently used device index inside device list.
	@return device index
*/
CTR_6002DR2_API int LMAL_CurrentDevice()
{
	return  getMainModule()->getSerPort()->CurrentDevice();
}

/**
	@ingroup ConnectionManager
	@brief Returns number of available devices.
	@return device count
*/
CTR_6002DR2_API int LMAL_DeviceCount()
{
	return getMainModule()->getSerPort()->GetDeviceList().size();
}

/**
	@ingroup ConnectionManager
	@brief Returns currently opened device name.
	@param name pointer to char array where to store device name
	@param count device name length
*/
CTR_6002DR2_API void LMAL_DeviceName(char *name, int index)
{
    vector<string> devices = getMainModule()->getSerPort()->GetDeviceList();
    if(index < devices.size() && index >= 0)
    {
        memcpy(name, devices[index].c_str(), strlen(devices[index].c_str()));
    }
}

/**
	@ingroup ConnectionManager
	@brief Loads connection settings from file.
	@param configFilename filename or full path to file
	@retval 0 failed
	@retval 1 succeeded
*/
CTR_6002DR2_API int LMAL_LoadSettings(const char *configFilename)
{
	return  0;
}
/**
	@ingroup ConnectionManager
	@brief Saves connection settings to file.
	@param configFilename filename or full path to file
	@retval 0 failed
	@retval 1 succeeded
*/
CTR_6002DR2_API int LMAL_SaveSettings(const char *configFilename)
{
	return  0;
}

/**
	@ingroup ConnectionManager
	@brief Sets custom parameter to connection port
	@param paramName parameter name
	@param value value to set the parameter
*/
CTR_6002DR2_API int LMAL_SetPortCustomParameter(char *paramName, char *value)
{
	return getMainModule()->getSerPort()->SetCustomParameter(paramName, value);
}

/**
	@ingroup ConnectionManager
	@brief Gets custom parameter from connection port
	@param paramName parameter name
	@param value current value of the parameter
*/
CTR_6002DR2_API int LMAL_GetPortCustomParameter(char *paramName, char *value)
{
	return getMainModule()->getSerPort()->GetCustomParameter(paramName, value);
}

/*
	Testing Module
*/
/**
	@ingroup Testing
	@brief Returns I and Q channel samples.
	@param Ich pointer to array for storing I channel samples
	@param Qch pointer to array for storing Q channel samples
	@param IQsize returns the number of samples
	@param itemsLeft returns number of sample packets left in buffer
*/
CTR_6002DR2_API void LMLL_Testing_GetSamples(float *Ich, float *Qch, int &IQsize, int &itemsLeft)
{
    SplitPacket *pkt;
    if(getMainModule()->getTesting()->m_hwDigiRed)
        pkt = new SplitPacket(DIGIRED_SPLIT_PACKET_SIZE);
    else
        pkt = new SplitPacket(DIGIGREEN_SPLIT_PACKET_SIZE);

    getMainModule()->getTesting()->m_SamplesFIFO->pop(pkt);
	itemsLeft = getMainModule()->getTesting()->m_fftFIFO->length();
    IQsize = pkt->size;
    if(Ich && Qch)
    {
        memcpy(Ich, pkt->Idata, sizeof(float)*pkt->size);
        memcpy(Qch, pkt->Qdata, sizeof(float)*pkt->size);
    }
}

/**
	@ingroup Testing
	@brief Returns FFT calculations data and results.
	@param *Ich pointer to array for storing I channel samples
	@param *Qch pointer to array for storing Q channel samples
	@param &IQSize returns the number of samples
	@param *FFTdataY pointer to array for storing frequency amplitudes from FFT
	@param &FFTsize returns number of amplitudes in FFTdataY
	@param &itemsLeft returns number of FFT packets left in buffer
*/
CTR_6002DR2_API void LMLL_Testing_GetFFTData(float *Ich, float *Qch, int &IQSize, float *FFTdataY, int &FFTsize, int &itemsLeft)
{
    FFTPacket fftPkt(getMainModule()->getTesting()->FFTsamples);
    getMainModule()->getTesting()->m_fftFIFO->freeze();
    itemsLeft = getMainModule()->getTesting()->m_fftFIFO->length();
    if(itemsLeft <= 0)
    {
        IQSize = 0;
        FFTsize = 0;
        itemsLeft = 0;
        return;
    }
	getMainModule()->getTesting()->m_fftFIFO->pop(&fftPkt);
	getMainModule()->getTesting()->m_fftFIFO->unfreeze();
	--itemsLeft;
	IQSize = getMainModule()->getTesting()->FFTsamples;

	if(Ich && Qch)
		for(int i=0; i<getMainModule()->getTesting()->FFTsamples; ++i)
		{
			Ich[i] = fftPkt.isamples[i];
			Qch[i] = fftPkt.qsamples[i];
		}

	if(FFTdataY)
		for(int i=0; i<fftPkt.size; i++)
		{
			FFTdataY[i] = fftPkt.amplitudes[i];
		}
	int size = fftPkt.size-1;

	//remove DC
	FFTdataY[0] = FFTdataY[1];
	FFTdataY[size/2] = (FFTdataY[size/2+1]+	FFTdataY[size/2-1])/2;
	FFTsize = size;
}

/**
	@ingroup Testing
	@brief Sets callback function for FFT window
*/
CTR_6002DR2_API void LMLL_Testing_SetCallbackUpdateInterface(void (*pCallbackFunction)(int, char *))
{
	getMainModule()->getTesting()->updateInterfaceCallback = pCallbackFunction;
}

/**
    @ingroup Testing
    @brief Calculates one FFT
*/
CTR_6002DR2_API bool LMLL_Testing_CalculateFFT()
{
    return getMainModule()->getTesting()->externalCalculateFFT();
}

/**
	@ingroup Testing
	@brief Starts data reading and calculating.
	Starts data samples reading from board and FFT calculations, received samples are used to calculate FFT
*/
CTR_6002DR2_API void LMLL_Testing_StartSdramRead()
{
	getMainModule()->getTesting()->StartSdramRead();
}
/**
	@ingroup Testing
	@brief Stops data reading and calculating.
	Stops threads used for data reading and calculations
*/
CTR_6002DR2_API void LMLL_Testing_StopSdramRead()
{
	getMainModule()->getTesting()->StopSdramRead();
}

/**
	@ingroup Testing
	@brief returns data rate from board in Bytes per seconds and number of data reading failures.
*/
CTR_6002DR2_API void LMLL_Testing_GetStatusInfo(unsigned long &bytesPs, unsigned int &failures)
{
	bytesPs = getMainModule()->getTesting()->m_bytesPerSecond;
	failures = getMainModule()->getTesting()->m_ulFailures;
}

/**
	@ingroup Testing
	@brief Enables FPGA reset signal
*/
CTR_6002DR2_API void LMLL_Testing_FPGAResetOn()
{
	getMainModule()->getTesting()->FPGAResetOn();
}

/**
	@ingroup Testing
	@brief Disables FPGA reset signal
*/
CTR_6002DR2_API void LMLL_Testing_FPGAResetOff()
{
    getMainModule()->getTesting()->FPGAResetOff();
}

CTR_6002DR2_API void LMLL_Testing_EnableFPGA(bool Tx, bool Rx)
{
	getMainModule()->getTesting()->EnableFPGA(Tx, Rx);
}

/**
	@ingroup Testing
	@brief Clears data left in chip's usb fifo buffer.
*/
CTR_6002DR2_API void LMLL_Testing_USBFIFOReset()
{
	getMainModule()->getTesting()->USBFIFOReset();
}

/**
	@ingroup Testing
	@brief Sets receiver data source
	@param ADC
	- false : data from NCO
	- true : data from ADC
*/
CTR_6002DR2_API void LMLL_Testing_SetRxDataSource(bool ADC)
{
	getMainModule()->getTesting()->SelectRxSource(ADC);
}

/**
	@ingroup Testing
	@brief Sets transiver data source
	@param FPGAtransmitter
	- false : NCO off
	- true : NCO on
*/
CTR_6002DR2_API void LMLL_Testing_SetTxDataSource(bool FPGAtransmitter)
{
	getMainModule()->getTesting()->SelectTxSource(FPGAtransmitter);
}

/**
	@ingroup Testing
	@brief Sets DC correction state
	@param on
	- false : DC correction disabled
	- true : DC correction enabled
*/
CTR_6002DR2_API void LMLL_Testing_SetDCCorrection(bool on)
{
	if(on)
		getMainModule()->getTesting()->turnOnDCcorrection();
	else
		getMainModule()->getTesting()->turnOffDCcorrection();
}

/**
    @ingroup Testing
    @brief Changes samples count used in FFT calculations
    @param samplesCount new samples count for FFT
    @return true if successfully changed samples count
*/
CTR_6002DR2_API bool LMLL_Testing_SetFFTSamplesCount(unsigned int samplesCount)
{
    return getMainModule()->getTesting()->setFFTSamplesCount(samplesCount);
}

/**
	@ingroup Transmitter
	@brief Starts transmitting samples
*/
CTR_6002DR2_API void LMLL_Transmitter_StartSendingSamples()
{
    getMainModule()->getTransmitter()->StartSendingSamples();
}

/**
	@ingroup Transmitter
	@brief Stops transmitting samples
*/
CTR_6002DR2_API void LMLL_Transmitter_StopSendingSamples()
{
    getMainModule()->getTransmitter()->StopSendingSamples();
}

/**
	@ingroup Transmitter
	@brief Generates sample data for transmitting
	@param freq Sinus frequency Hz
	@param amplitude Signal amplitude
	@param samplingRate Sampling frequency Hz
*/
CTR_6002DR2_API void LMLL_Transmitter_GenerateSamples(double freqHz, double amplitude, double samplingRateHz)
{
    getMainModule()->getTransmitter()->GenerateSamples(freqHz, amplitude, samplingRateHz);
}

/**
	@ingroup Transmitter
	@brief Loads samples data for transmitting from text or binary file
	@param filename filename or full path to file
	@param binary specifies file format
*/
CTR_6002DR2_API void LMLL_Transmitter_LoadSamplesFromFile(char *filename, bool binary)
{
    getMainModule()->getTransmitter()->LoadSamplesFromFile(filename, binary);
}

/**
	@ingroup Transmitter
	@brief Loads samples data for transmitting from array
	@param filename filename or full path to file
	@param binary specifies file format
*/
CTR_6002DR2_API void LMLL_Transmitter_LoadSamplesFromArray(unsigned char*array, long length)
{
    getMainModule()->getTransmitter()->SetPlaybackPattern(array, length);
}

/**
	@ingroup Transmitter
	@brief Returns samples that are prepared for transmitting
	@param Ichannel pointer to array where to place I channel data
	@param Qchannel pointer to array where to place Q channel data
	@param samplesCount number of samples that will be returned.

	Ichannel and Qchannel arrays must be big enough to store all samples. If NULL pointers are given, no data will be copied only samples count will be returned.
*/
CTR_6002DR2_API void LMLL_Transmitter_GetSamples(float *Ichannel, float *Qchannel, int &samplesCount)
{
    getMainModule()->getTransmitter()->GetSamples(Ichannel, Qchannel, samplesCount);
}

CTR_6002DR2_API void LMLL_ADF_SetFrefFvco(float Fref, float Fvco, int &rcount, int &ncount)
{
    getMainModule()->getADF()->txtFref = Fref;
    getMainModule()->getADF()->txtFvco = Fvco;
    getMainModule()->getADF()->CalculateRN();
    rcount = getMainModule()->getADF()->txtRCnt;
    ncount = getMainModule()->getADF()->txtNCnt;
}

CTR_6002DR2_API void LMLL_ADF_SetReferenceCounterLatch(int Ldp, int Abw, int refCounter)
{
    getMainModule()->getADF()->cmbLDP.itemIndex = Ldp;
    getMainModule()->getADF()->cmbABW.itemIndex = Abw;
    getMainModule()->getADF()->txtRCnt = refCounter;

}

CTR_6002DR2_API void LMLL_ADF_SetNCounterLatch(int CPgain, int NCounter)
{
    getMainModule()->getADF()->cmbCPG.itemIndex = CPgain;
    getMainModule()->getADF()->txtNCnt = NCounter;
}

CTR_6002DR2_API void LMLL_ADF_SetFunctionLatch(int currentSetting1, int currentSetting2, int timerCounter, int fastLock, int muxoutControl)
{
    getMainModule()->getADF()->cmbCS1_f.itemIndex = currentSetting1;
    getMainModule()->getADF()->cmbCS2_f.itemIndex = currentSetting2;
    getMainModule()->getADF()->cmbTC_f.itemIndex = timerCounter;
    getMainModule()->getADF()->cmbFL_f.itemIndex = fastLock;
    getMainModule()->getADF()->cmbMOC_f.itemIndex = muxoutControl;
}
CTR_6002DR2_API void LMLL_ADF_SetFunctionLatchRgr(int pdPol, int pd1, int pd2, int counterReset, int cpState)
{
    getMainModule()->getADF()->rgrPD1_f.itemIndex = pd1;
    getMainModule()->getADF()->rgrPD2_f.itemIndex = pd2;
    getMainModule()->getADF()->rgrPDP_f.itemIndex = pdPol;
    getMainModule()->getADF()->rgrCR_f.itemIndex = counterReset;
    getMainModule()->getADF()->rgrCPS_f.itemIndex = cpState;
}
CTR_6002DR2_API void LMLL_ADF_SetInitializationLatch(int currentSetting1, int currentSetting2, int timerCounter, int fastLock, int muxoutControl)
{
    getMainModule()->getADF()->cmbCS1_i.itemIndex = currentSetting1;
    getMainModule()->getADF()->cmbCS2_i.itemIndex = currentSetting2;
    getMainModule()->getADF()->cmbTC_i.itemIndex = timerCounter;
    getMainModule()->getADF()->cmbFL_i.itemIndex = fastLock;
    getMainModule()->getADF()->cmbMOC_i.itemIndex = muxoutControl;
}
CTR_6002DR2_API void LMLL_ADF_SetInitializationLatchRgr(int pdPol, int pd1, int pd2, int counterReset, int cpState)
{
    getMainModule()->getADF()->rgrPD1_i.itemIndex = pd1;
    getMainModule()->getADF()->rgrPD2_i.itemIndex = pd2;
    getMainModule()->getADF()->rgrPDP_i.itemIndex = pdPol;
    getMainModule()->getADF()->rgrCR_i.itemIndex = counterReset;
    getMainModule()->getADF()->rgrCPS_i.itemIndex = cpState;
}

CTR_6002DR2_API void LMLL_ADF_SendConfig()
{
    getMainModule()->getADF()->SendConfig();
}

}


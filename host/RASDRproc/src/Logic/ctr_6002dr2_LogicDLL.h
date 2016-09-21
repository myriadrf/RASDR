// -----------------------------------------------------------------------------
// FILE:        "ctr_6002dr2_LogicDLL.h"
// DESCRIPTION: "Header File"
// DATE:        "05/09/2015 06:44 AM "
// AUTHOR(s):   Lime Microsystems, Paul L. Oxley
// Copyright:   Society of Amateur Radio Astronomers (2014-2015)
//
// Based on original work from Zydrunas Tamosevicius (Lime Microsystems, Ltd.)
// and distributed under the Apache License 2.0 at:
// https://github.com/myriadrf/myriadrf-utils
//
// The RASDRviewer version has been specifically modified for Radio Astronomy
// by Paul L. Oxley for the Society of Amateur Radio Astronomers.  These
// modifications are provided to you under the Gnu Public License version 2.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// REVISIONS:   as appropriate
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// FILE: 		ctr_6002dr2_LogicDLL.h
// DESCRIPTION:	Header for ctr_6002dr2_LogicDLL.cpp
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#ifndef CTR_6002DR2_LOGICDLL_H
#define CTR_6002DR2_LOGICDLL_H

#ifdef EXPORT_DLL
    #define CTR_6002DR2_LOGICDLL_EXPORTS

    #ifdef CTR_6002DR2_LOGICDLL_EXPORTS
    #define CTR_6002DR2_API __declspec(dllexport)
    #else
    #define CTR_6002DR2_API __declspec(dllimport)
    #endif
#else
    #define CTR_6002DR2_API
#endif

#include <stddef.h>
#include <cstddef>



struct sVcoVsCap;

extern "C"
{
//==============================================================================
// Application level commands
//==============================================================================

CTR_6002DR2_API int LMAL_Initialize();
CTR_6002DR2_API void LMAL_Quit();
CTR_6002DR2_API void LMAL_SetReferenceClock(double refClk_Hz);
CTR_6002DR2_API double LMAL_GetReferenceClock();
CTR_6002DR2_API void LMAL_TxPLL_SetFrequency(double FreqGHz);
CTR_6002DR2_API void LMAL_RxPLL_SetFrequency(double FreqGHz);
CTR_6002DR2_API void LMAL_TopDCStartCalibration();
CTR_6002DR2_API void LMAL_CalibrateTx();
CTR_6002DR2_API void LMAL_CalibrateRx();
CTR_6002DR2_API void LMAL_CalibrateLPFCore();

CTR_6002DR2_API void LMAL_SetRxBypass(int index);
CTR_6002DR2_API void LMAL_SetTxBypass(int index);
CTR_6002DR2_API void LMAL_SetLoopback(int index);


CTR_6002DR2_API void LMAL_SelectActiveLNA(int index);
CTR_6002DR2_API bool LMAL_TestRegisters();

CTR_6002DR2_API void LMAL_GetVerRevMask(int &ver, int &rev, int &mask);
CTR_6002DR2_API void LMAL_EnableAllSPIClocks();
CTR_6002DR2_API void LMAL_RestoreAllSPIClocks();

CTR_6002DR2_API void LMAL_Top_PowerOn(bool on);
CTR_6002DR2_API void LMAL_TxLPF_PowerOn(bool on);
CTR_6002DR2_API void LMAL_RxLPF_PowerOn(bool on);
CTR_6002DR2_API void LMAL_TxPLL_PowerOn(bool on);
CTR_6002DR2_API void LMAL_RxPLL_PowerOn(bool on);

CTR_6002DR2_API void LMAL_RxFE_PowerOn(bool on);
CTR_6002DR2_API void LMAL_RxFE_LNAPowerOn(bool on);
CTR_6002DR2_API void LMAL_RxVGA2_PowerOn(bool on);

// Main Module
CTR_6002DR2_API void LMAL_MainSetCallbackInterfaceUpdate(void (*pCallbackFunction)(int, const char *) );
CTR_6002DR2_API void LMAL_MainFileNewExecute();
CTR_6002DR2_API void LMAL_MainFileSaveAs(char* link);
CTR_6002DR2_API void LMAL_MainFileSave();

CTR_6002DR2_API void LMAL_MainReadSettingsFromChip();
CTR_6002DR2_API void LMAL_MainSetAutoDownload(bool state);
CTR_6002DR2_API void LMAL_MainDownload();
CTR_6002DR2_API void LMAL_MainOpenFile(char *filename);

CTR_6002DR2_API void LMAL_MainSetDLTXBand(int index);
CTR_6002DR2_API void LMAL_MainSetDLTXChannel(int index);
CTR_6002DR2_API void LMAL_MainSetULRXBand(int index);
CTR_6002DR2_API void LMAL_MainSetULRXChannel(int index);
CTR_6002DR2_API double LMAL_MainGetDLTXFreq();
CTR_6002DR2_API double LMAL_MainGetULRXFreq();

CTR_6002DR2_API void LMAL_MainGetDLTXBands(char** bands, int &count);
CTR_6002DR2_API void LMAL_MainGetULRXBands(char** bands, int &count);

CTR_6002DR2_API void LMAL_MainGetDLTXChannels(char** channels, int &count);
CTR_6002DR2_API void LMAL_MainGetULRXChannels(char** channels, int &count);

CTR_6002DR2_API void LMAL_MainSetCurrentFileName(const char *filename);
CTR_6002DR2_API void LMAL_MainCompareChipToGUI();
CTR_6002DR2_API void LMAL_MainReadConfiguration(char *filename);
CTR_6002DR2_API void LMAL_MainSaveUnderRVF_Format(const char *filename, int dec);
CTR_6002DR2_API void LMAL_MainSaveUnderRFIF_Format(const char *filename, int rfifParam);
CTR_6002DR2_API void LMAL_MainSaveRegisters(const char *filename);

CTR_6002DR2_API unsigned int LMAL_MainGetMessageLogLength();
CTR_6002DR2_API void LMAL_MainGetMessageLogMessages(char *buffer);

CTR_6002DR2_API unsigned int LMAL_MainRegTestGetLogLength();
CTR_6002DR2_API void LMAL_MainRegTestGetLogMessages(char *buffer);

// ---End of main module

//==============================================================================
// Low level commands
//==============================================================================

// TxRf Module
// ============================================================================
CTR_6002DR2_API char LMLL_TxRfGetAddr();

CTR_6002DR2_API void LMLL_TxRfSetPwrTxRfMods(bool enabled);
CTR_6002DR2_API bool LMLL_TxRfGetPwrTxRfMods();

CTR_6002DR2_API void LMLL_TxRfSetDecode(int index);
CTR_6002DR2_API int LMLL_TxRfGetDecode();

CTR_6002DR2_API void LMLL_TxRfSetVga1G_u(int index);
CTR_6002DR2_API int LMLL_TxRfGetVga1G_u();

CTR_6002DR2_API void LMLL_TxRfSetVga1DcI(int index);
CTR_6002DR2_API int LMLL_TxRfGetVga1DcI();

CTR_6002DR2_API void LMLL_TxRfSetVga1DcQ(int index);
CTR_6002DR2_API int LMLL_TxRfGetVga1DcQ();

CTR_6002DR2_API void LMLL_TxRfSetPA(int index);
CTR_6002DR2_API int LMLL_TxRfGetPA();

CTR_6002DR2_API void LMLL_TxRfSetVga2G_u(int index);
CTR_6002DR2_API int LMLL_TxRfGetVga2G_u();

CTR_6002DR2_API void LMLL_TxRfSetPwrVga1_I(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetPwrVga1_I();

CTR_6002DR2_API void LMLL_TxRfSetPwrVga2(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetPwrVga2();

CTR_6002DR2_API void LMLL_TxRfSetVga1G_t(int index);
CTR_6002DR2_API int LMLL_TxRfGetVga1G_t();

CTR_6002DR2_API void LMLL_TxRfSetVga2G_t(int index);
CTR_6002DR2_API int LMLL_TxRfGetVga2G_t();

CTR_6002DR2_API void LMLL_TxRfSetPwrVga1_Q(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetPwrVga1_Q();

CTR_6002DR2_API void LMLL_TxRfSetLOOPBBEN(int index);
CTR_6002DR2_API int LMLL_TxRfGetLOOPBBEN();

CTR_6002DR2_API void LMLL_TxRfSetPD_DRVAUX(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetPD_DRVAUX();

CTR_6002DR2_API void LMLL_TxRfSetPD_PKDET(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetPD_PKDET();

CTR_6002DR2_API void LMLL_TxRfSetENVD(int index);
CTR_6002DR2_API int LMLL_TxRfGetENVD();

CTR_6002DR2_API void LMLL_TxRfSetENVD2(int index);
CTR_6002DR2_API int LMLL_TxRfGetENVD2();

CTR_6002DR2_API void LMLL_TxRfSetPKDBW(int index);
CTR_6002DR2_API int LMLL_TxRfGetPKDBW();

CTR_6002DR2_API void LMLL_TxRfSetFST_PKDET(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetFST_PKDET();

CTR_6002DR2_API void LMLL_TxRfSetFST_TXHFBIAS(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetFST_TXHFBIAS();

CTR_6002DR2_API void LMLL_TxRfSetICT_TXLOBUF(int index);
CTR_6002DR2_API int LMLL_TxRfGetICT_TXLOBUF();

CTR_6002DR2_API void LMLL_TxRfSetVBCAS_TXDRV(int index);
CTR_6002DR2_API int LMLL_TxRfGetVBCAS_TXDRV();

CTR_6002DR2_API void LMLL_TxRfSetICT_TXMIX(int index);
CTR_6002DR2_API int LMLL_TxRfGetICT_TXMIX();

CTR_6002DR2_API void LMLL_TxRfSetICT_TXDRV(int index);
CTR_6002DR2_API int LMLL_TxRfGetICT_TXDRV();

CTR_6002DR2_API void LMLL_TxRfSetPD_TXLOBUF(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetPD_TXLOBUF();

CTR_6002DR2_API void LMLL_TxRfSetPD_TXDRV(bool state);
CTR_6002DR2_API bool LMLL_TxRfGetPD_TXDRV();
// ============================================================================
// End of TxRf Module

// TxPLL Module
// ============================================================================
CTR_6002DR2_API unsigned int LMLL_TxPLLGetVcoCapLogLength();
CTR_6002DR2_API void LMLL_TxPLLGetVcoCapLogMessages(char *buffer);

CTR_6002DR2_API char LMLL_TxPLLGetAddr();
CTR_6002DR2_API void LMLL_TxPLLSetRefClk(double RefClk);
CTR_6002DR2_API double LMLL_TxPLLGetRefClk();
CTR_6002DR2_API int LMLL_TxPLLGetVTuneState();

CTR_6002DR2_API bool LMLL_TxPLLBIST_GetState();
CTR_6002DR2_API unsigned int LMLL_TxPLLBIST_GetSignature();
CTR_6002DR2_API void LMLL_TxPLLBIST_Start();

CTR_6002DR2_API double LMLL_TxPLLGetFrequency();
CTR_6002DR2_API void LMLL_TxPLLChooseVcoCap();

CTR_6002DR2_API void LMLL_TxPLLSetDITHEN(int index);
CTR_6002DR2_API int LMLL_TxPLLGetDITHEN();

CTR_6002DR2_API void LMLL_TxPLLSetDITHN(int index);
CTR_6002DR2_API int LMLL_TxPLLGetDITHN();

CTR_6002DR2_API void LMLL_TxPLLSetPwrPllMods(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetPwrPllMods();

CTR_6002DR2_API void LMLL_TxPLLSetDecode(int index);
CTR_6002DR2_API int LMLL_TxPLLGetDecode();

CTR_6002DR2_API void LMLL_TxPLLSetMODE(int index);
CTR_6002DR2_API int LMLL_TxPLLGetMODE();

CTR_6002DR2_API void LMLL_TxPLLSetSELVCO(int index);
CTR_6002DR2_API int LMLL_TxPLLGetSELVCO();

CTR_6002DR2_API void LMLL_TxPLLSetFRANGE(int index);
CTR_6002DR2_API int LMLL_TxPLLGetFRANGE();

CTR_6002DR2_API void LMLL_TxPLLSetICHP(int index);
CTR_6002DR2_API int LMLL_TxPLLGetICHP();

CTR_6002DR2_API void LMLL_TxPLLSetOFFUP(int index);
CTR_6002DR2_API int LMLL_TxPLLGetOFFUP();

CTR_6002DR2_API void LMLL_TxPLLSetOFFDOWN(int index);
CTR_6002DR2_API int LMLL_TxPLLGetOFFDOWN();

CTR_6002DR2_API void LMLL_TxPLLSetVCOCAP(int index);
CTR_6002DR2_API int LMLL_TxPLLGetVCOCAP();

CTR_6002DR2_API void LMLL_TxPLLSetBCODE(int code);
CTR_6002DR2_API int LMLL_TxPLLGetBCODE();

CTR_6002DR2_API void LMLL_TxPLLSetACODE(int index);
CTR_6002DR2_API int LMLL_TxPLLGetACODE();

CTR_6002DR2_API void LMLL_TxPLLSetENLOBUF(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetENLOBUF();

CTR_6002DR2_API void LMLL_TxPLLSetENLAMP(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetENLAMP();

CTR_6002DR2_API void LMLL_TxPLLSetPFDPD(bool poweredUp);
CTR_6002DR2_API bool LMLL_TxPLLGetPFDPD();

CTR_6002DR2_API void LMLL_TxPLLSetENFEEDDIV(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetENFEEDDIV();

CTR_6002DR2_API void LMLL_TxPLLSetPD_VCOCOMP_SX(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetPD_VCOCOMP_SX();

CTR_6002DR2_API void LMLL_TxPLLSetOEN_TSTD_SX(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetOEN_TSTD_SX();

CTR_6002DR2_API void LMLL_TxPLLSetPASSEN_TSTOD_SD(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetPASSEN_TSTOD_SD();

CTR_6002DR2_API void LMLL_TxPLLTune();

CTR_6002DR2_API void LMLL_TxPLLSetPFDCLKP(bool state);
CTR_6002DR2_API bool LMLL_TxPLLGetPFDCLKP();

CTR_6002DR2_API void LMLL_TxPLLSetTRI(bool state);
CTR_6002DR2_API bool LMLL_TxPLLGetTRI();

CTR_6002DR2_API void LMLL_TxPLLSetPOL(bool mode);
CTR_6002DR2_API bool LMLL_TxPLLGetPOL();

CTR_6002DR2_API void LMLL_TxPLLSetAUTOBYP(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetAUTOBYP();

CTR_6002DR2_API void LMLL_TxPLLSetEN_PFD_UP(bool enabled);
CTR_6002DR2_API bool LMLL_TxPLLGetEN_PFD_UP();

CTR_6002DR2_API void LMLL_TxPLLSetBYPVCOREG(bool state);
CTR_6002DR2_API bool LMLL_TxPLLGetBYPVCOREG();

CTR_6002DR2_API void LMLL_TxPLLSetPDVCOREG(bool state);
CTR_6002DR2_API bool LMLL_TxPLLGetPDVCOREG();

CTR_6002DR2_API void LMLL_TxPLLSetFSTVCOBG(bool state);
CTR_6002DR2_API bool LMLL_TxPLLGetFSTVCOBG();

CTR_6002DR2_API void LMLL_TxPLLSetVOVCOREG(int index);
CTR_6002DR2_API int LMLL_TxPLLGetVOVCOREG();

CTR_6002DR2_API void LMLL_TxPLLSetBCLKSEL(int index);
CTR_6002DR2_API int LMLL_TxPLLGetBCLKSEL();

CTR_6002DR2_API void LMLL_TxPLLSetBINSEL(int index);
CTR_6002DR2_API int LMLL_TxPLLGetBINSEL();

CTR_6002DR2_API void LMLL_TxPLLGetValuesForIntegerMode(int &divN, double &Fvco, double &Fvco2, double &Fvco4, double &Fvco8, double &Fvco16);
CTR_6002DR2_API void LMLL_TxPLLGetValuesForFractionalMode(int &nInt, int &nFrac, double &div, double &ROutF, double &VcoF);
// ============================================================================
// End of TxPLL

// RxPLL Module
// ============================================================================
CTR_6002DR2_API unsigned int LMLL_RxPLLGetVcoCapLogLength();
CTR_6002DR2_API void LMLL_RxPLLGetVcoCapLogMessages(char *buffer);

CTR_6002DR2_API char LMLL_RxPLLGetAddr();
CTR_6002DR2_API void LMLL_RxPLLSetRefClk(double RefClk);
CTR_6002DR2_API double LMLL_RxPLLGetRefClk();
CTR_6002DR2_API int LMLL_RxPLLGetVTuneState();

CTR_6002DR2_API bool LMLL_RxPLLBIST_GetState();
CTR_6002DR2_API unsigned int LMLL_RxPLLBIST_GetSignature();

CTR_6002DR2_API void LMLL_RxPLLBIST_Start();

CTR_6002DR2_API double LMLL_RxPLLGetFrequency();
CTR_6002DR2_API void LMLL_RxPLLChooseVcoCap();

CTR_6002DR2_API void LMLL_RxPLLSetDITHEN(int index);
CTR_6002DR2_API int LMLL_RxPLLGetDITHEN();

CTR_6002DR2_API void LMLL_RxPLLSetDITHN(int index);
CTR_6002DR2_API int LMLL_RxPLLGetDITHN();

CTR_6002DR2_API void LMLL_RxPLLSetPwrPllMods(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetPwrPllMods();

CTR_6002DR2_API void LMLL_RxPLLSetDecode(int index);
CTR_6002DR2_API int LMLL_RxPLLGetDecode();

CTR_6002DR2_API void LMLL_RxPLLSetMODE(int index);
CTR_6002DR2_API int LMLL_RxPLLGetMODE();

CTR_6002DR2_API void LMLL_RxPLLSetSELVCO(int index);
CTR_6002DR2_API int LMLL_RxPLLGetSELVCO();

CTR_6002DR2_API void LMLL_RxPLLSetFRANGE(int index);
CTR_6002DR2_API int LMLL_RxPLLGetFRANGE();

CTR_6002DR2_API void LMLL_RxPLLSetSELOUT(int index);
CTR_6002DR2_API int LMLL_RxPLLGetSELOUT();

CTR_6002DR2_API void LMLL_RxPLLSetICHP(int index);
CTR_6002DR2_API int LMLL_RxPLLGetICHP();

CTR_6002DR2_API void LMLL_RxPLLSetOFFUP(int index);
CTR_6002DR2_API int LMLL_RxPLLGetOFFUP();

CTR_6002DR2_API void LMLL_RxPLLSetOFFDOWN(int index);
CTR_6002DR2_API int LMLL_RxPLLGetOFFDOWN();

CTR_6002DR2_API void LMLL_RxPLLSetVCOCAP(int index);
CTR_6002DR2_API int LMLL_RxPLLGetVCOCAP();

CTR_6002DR2_API void LMLL_RxPLLSetBCODE(int index);
CTR_6002DR2_API int LMLL_RxPLLGetBCODE();

CTR_6002DR2_API void LMLL_RxPLLSetACODE(int index);
CTR_6002DR2_API int LMLL_RxPLLGetACODE();

CTR_6002DR2_API void LMLL_RxPLLSetENLOBUF(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetENLOBUF();

CTR_6002DR2_API void LMLL_RxPLLSetENLAMP(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetENLAMP();

CTR_6002DR2_API void LMLL_RxPLLSetPFDPD(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetPFDPD();

CTR_6002DR2_API void LMLL_RxPLLSetENFEEDDIV(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetENFEEDDIV();

CTR_6002DR2_API void LMLL_RxPLLSetPD_VCOCOMP_SX(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetPD_VCOCOMP_SX();

CTR_6002DR2_API void LMLL_RxPLLSetOEN_TSTD_SX(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetOEN_TSTD_SX();

CTR_6002DR2_API void LMLL_RxPLLSetPASSEN_TSTOD_SD(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetPASSEN_TSTOD_SD();

CTR_6002DR2_API void LMLL_RxPLLTune();

CTR_6002DR2_API void LMLL_RxPLLSetPFDCLKP(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetPFDCLKP();

CTR_6002DR2_API void LMLL_RxPLLSetTRI(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetTRI();

CTR_6002DR2_API void LMLL_RxPLLSetPOL(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetPOL();

CTR_6002DR2_API void LMLL_RxPLLSetAUTOBYP(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetAUTOBYP();

CTR_6002DR2_API void LMLL_RxPLLSetEN_PFD_UP(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetEN_PFD_UP();

CTR_6002DR2_API void LMLL_RxPLLSetBYPVCOREG(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetBYPVCOREG();

CTR_6002DR2_API void LMLL_RxPLLSetPDVCOREG(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetPDVCOREG();

CTR_6002DR2_API void LMLL_RxPLLSetFSTVCOBG(bool checked);
CTR_6002DR2_API bool LMLL_RxPLLGetFSTVCOBG();

CTR_6002DR2_API void LMLL_RxPLLSetVOVCOREG(int index);
CTR_6002DR2_API int LMLL_RxPLLGetVOVCOREG();

CTR_6002DR2_API void LMLL_RxPLLSetBCLKSEL(int index);
CTR_6002DR2_API int LMLL_RxPLLGetBCLKSEL();

CTR_6002DR2_API void LMLL_RxPLLSetBINSEL(int index);
CTR_6002DR2_API int LMLL_RxPLLGetBINSEL();

CTR_6002DR2_API void LMLL_RxPLLGetValuesForIntegerMode(int &divN, double &Fvco, double &Fvco2, double &Fvco4, double &Fvco8, double &Fvco16);
CTR_6002DR2_API void LMLL_RxPLLGetValuesForFractionalMode(int &nInt, int &nFrac, double &div, double &ROutF, double &VcoF);
// ============================================================================
// End of RxPLL

//  TxLPF Module
//==============================================================================
CTR_6002DR2_API char LMLL_TxLPFGetAddr();

CTR_6002DR2_API void LMLL_TxLPFDCResetCalibration();
CTR_6002DR2_API void LMLL_TxLPFDCLoadValues(unsigned int value);
CTR_6002DR2_API void LMLL_TxLPFDCStartCalibration();
CTR_6002DR2_API void LMLL_TxLPFDCReadValues(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);

CTR_6002DR2_API void LMLL_TxLPFSetDecode(int index);
CTR_6002DR2_API int LMLL_TxLPFGetDecode();

CTR_6002DR2_API void LMLL_TxLPFSetLpfBw(int index);
CTR_6002DR2_API int LMLL_TxLPFGetLpfBw();

CTR_6002DR2_API void LMLL_TxLPFSetDCOffset(int index);
CTR_6002DR2_API int LMLL_TxLPFGetDCOffset();

CTR_6002DR2_API void LMLL_TxLPFSetRcCal(int index);
CTR_6002DR2_API int LMLL_TxLPFGetRcCal();

CTR_6002DR2_API void LMLL_TxLPFSetPwrLpf(bool state);
CTR_6002DR2_API bool LMLL_TxLPFGetPwrLpf();

CTR_6002DR2_API void LMLL_TxLPFSetPwrDCDac(bool state);
CTR_6002DR2_API bool LMLL_TxLPFGetPwrDCDac();

CTR_6002DR2_API void LMLL_TxLPFSetPwrDCRef(bool state);
CTR_6002DR2_API bool LMLL_TxLPFGetPwrDCRef();

CTR_6002DR2_API void LMLL_TxLPFSetPwrDCCmpr(bool state);
CTR_6002DR2_API bool LMLL_TxLPFGetPwrDCCmpr();

CTR_6002DR2_API void LMLL_TxLPFSetDCCalAddr(int index);
CTR_6002DR2_API int LMLL_TxLPFGetDCCalAddr();

CTR_6002DR2_API void LMLL_TxLPFSetPwrLpfMods(bool state);
CTR_6002DR2_API bool LMLL_TxLPFGetPwrLpfMods();

CTR_6002DR2_API void LMLL_TxLPFSetLpfByp(int index);
CTR_6002DR2_API int LMLL_TxLPFGetLpfByp();

CTR_6002DR2_API void LMLL_TxLPFSetTX_DACBUF_EN(bool state);
CTR_6002DR2_API bool LMLL_TxLPFGetTX_DACBUF_EN();

CTR_6002DR2_API void LMLL_TxLPFGetDCCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);
//==============================================================================
// End of TxLPF

//  RxLPF Module
//==============================================================================
CTR_6002DR2_API char LMLL_RxLPFGetAddr();

CTR_6002DR2_API void LMLL_RxLPFDCResetCalibration();
CTR_6002DR2_API void LMLL_RxLPFDCLoadValues(unsigned int value);
CTR_6002DR2_API void LMLL_RxLPFDCStartCalibration();
CTR_6002DR2_API void LMLL_RxLPFDCReadValues(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);

CTR_6002DR2_API void LMLL_RxLPFSetDecode(int index);
CTR_6002DR2_API int LMLL_RxLPFGetDecode();

CTR_6002DR2_API void LMLL_RxLPFSetLpfBw(int index);
CTR_6002DR2_API int LMLL_RxLPFGetLpfBw();

CTR_6002DR2_API void LMLL_RxLPFSetDCOffset(int index);
CTR_6002DR2_API int LMLL_RxLPFGetDCOffset();

CTR_6002DR2_API void LMLL_RxLPFSetRcCal(int index);
CTR_6002DR2_API int LMLL_RxLPFGetRcCal();

CTR_6002DR2_API void LMLL_RxLPFSetPwrLpf(bool state);
CTR_6002DR2_API bool LMLL_RxLPFGetPwrLpf();

CTR_6002DR2_API void LMLL_RxLPFSetPwrDCDac(bool state);
CTR_6002DR2_API bool LMLL_RxLPFGetPwrDCDac();

CTR_6002DR2_API void LMLL_RxLPFSetPwrDCRef(bool state);
CTR_6002DR2_API bool LMLL_RxLPFGetPwrDCRef();

CTR_6002DR2_API void LMLL_RxLPFSetPwrDCCmpr(bool state);
CTR_6002DR2_API bool LMLL_RxLPFGetPwrDCCmpr();

CTR_6002DR2_API void LMLL_RxLPFSetDCCalAddr(int index);
CTR_6002DR2_API int LMLL_RxLPFGetDCCalAddr();

CTR_6002DR2_API void LMLL_RxLPFSetPwrLpfMods(bool state);
CTR_6002DR2_API bool LMLL_RxLPFGetPwrLpfMods();

CTR_6002DR2_API void LMLL_RxLPFSetLpfByp(int index);
CTR_6002DR2_API int LMLL_RxLPFGetLpfByp();

CTR_6002DR2_API void LMLL_RxLPFGetDCCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);
//==============================================================================
// End of RxLPF

// Top Module
//==============================================================================
CTR_6002DR2_API void LMLL_TopSetDecode(int index);
CTR_6002DR2_API int LMLL_TopGetDecode();

CTR_6002DR2_API void LMLL_TopSetSpiMode(int index);
CTR_6002DR2_API int LMLL_TopGetSpiMode();

CTR_6002DR2_API void LMLL_TopSetDsmRst(int index);
CTR_6002DR2_API int LMLL_TopGetDsmRst();

CTR_6002DR2_API void LMLL_TopSetRxTestModeEn(bool state);
CTR_6002DR2_API bool LMLL_TopGetRxTestModeEn();

CTR_6002DR2_API void LMLL_TopSetSpiClkBuf(int index, bool state);
CTR_6002DR2_API bool LMLL_TopGetSpiClkBuf(int index);

CTR_6002DR2_API void LMLL_TopSetRFLB(int index);
CTR_6002DR2_API int LMLL_TopGetRFLB();

CTR_6002DR2_API void LMLL_TopSetLpfCalRst(bool state);
CTR_6002DR2_API bool LMLL_TopGetLpfCalRst();

CTR_6002DR2_API void LMLL_TopSetLpfCalEn(bool state);
CTR_6002DR2_API bool LMLL_TopGetLpfCalEn();

CTR_6002DR2_API void LMLL_TopSetLpfCalEnEnf(bool state);
CTR_6002DR2_API bool LMLL_TopGetLpfCalEnEnf();

CTR_6002DR2_API void LMLL_TopSetLpfCalCode(int index);
CTR_6002DR2_API int LMLL_TopGetLpfCalCode();

CTR_6002DR2_API void LMLL_TopSetLpfCalBw(int index);
CTR_6002DR2_API int LMLL_TopGetLpfCalBw();

CTR_6002DR2_API void LMLL_TopSetPwrTopMods(bool state);
CTR_6002DR2_API bool LMLL_TopGetPwrTopMods();

CTR_6002DR2_API void LMLL_TopSetPwrSoftTx(bool state);
CTR_6002DR2_API bool LMLL_TopGetPwrSoftTx();

CTR_6002DR2_API void LMLL_TopSetPwrSoftRx(bool state);
CTR_6002DR2_API bool LMLL_TopGetPwrSoftRx();

CTR_6002DR2_API void LMLL_TopSetPwrLpfCal(bool state);
CTR_6002DR2_API bool LMLL_TopGetPwrLpfCal();

CTR_6002DR2_API void LMLL_TopSetPwrRfLbsw(bool state);
CTR_6002DR2_API bool LMLL_TopGetPwrRfLbsw();

CTR_6002DR2_API void LMLL_TopSetDCCalAddr(int index);
CTR_6002DR2_API int LMLL_TopGetDCCalAddr();

CTR_6002DR2_API void LMLL_TopResetOn();
CTR_6002DR2_API void LMLL_TopResetOff();

CTR_6002DR2_API void LMLL_TopSetBBLB(int index);
CTR_6002DR2_API int LMLL_TopGetBBLB();

CTR_6002DR2_API void LMLL_TopSetCLKSEL_LPFCAL(int index);
CTR_6002DR2_API int LMLL_TopGetCLKSEL_LPFCAL();

CTR_6002DR2_API void LMLL_TopSetPD_CLKLPFCAL(bool state);
CTR_6002DR2_API bool LMLL_TopGetPD_CLKLPFCAL();

CTR_6002DR2_API void LMLL_TopSetRXOUTSW(int index);
CTR_6002DR2_API int LMLL_TopGetRXOUTSW();

CTR_6002DR2_API void LMLL_TopSetFDDTDD(int index);
CTR_6002DR2_API int LMLL_TopGetFDDTDD();

CTR_6002DR2_API void LMLL_TopSetTDDMOD(int index);
CTR_6002DR2_API int LMLL_TopGetTDDMOD();

CTR_6002DR2_API void LMLL_TopSetPDXCOBUF(bool state);
CTR_6002DR2_API bool LMLL_TopGetPDXCOBUF();

CTR_6002DR2_API void LMLL_TopSetSLFBXCOBUF(bool state);
CTR_6002DR2_API bool LMLL_TopGetSLFBXCOBUF();

CTR_6002DR2_API void LMLL_TopSetBYPXCOBUF(bool state);
CTR_6002DR2_API bool LMLL_TopGetBYPXCOBUF();

CTR_6002DR2_API void LMLL_TopGetDCCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);
CTR_6002DR2_API int LMLL_TopGetRCCAL_LPFCAL();

CTR_6002DR2_API void LMLL_TopDCResetCalibration();
CTR_6002DR2_API void LMLL_TopDCLoadValues(unsigned int value);
CTR_6002DR2_API void LMLL_TopDCReadValues(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);
//==============================================================================
// End of Top Module

// RxVGA2 Module
//==============================================================================
CTR_6002DR2_API char LMLL_RxVGA2GetAddr();

CTR_6002DR2_API void LMLL_RxVGA2DCResetCalibration();
CTR_6002DR2_API void LMLL_RxVGA2DCLoadValues(unsigned int value);
CTR_6002DR2_API void LMLL_RxVGA2DCStartCalibration();
CTR_6002DR2_API void LMLL_RxVGA2DCReadValues(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);

CTR_6002DR2_API int LMLL_RxVGA2GetRXVGA2Gain();
CTR_6002DR2_API void LMLL_RxVGA2SetRXVGA2Gain(int Ind);

CTR_6002DR2_API void LMLL_RxVGA2SetPwrVGA2Mods(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrVGA2Mods();

CTR_6002DR2_API void LMLL_RxVGA2SetDecode(int index);
CTR_6002DR2_API int LMLL_RxVGA2GetDecode();

CTR_6002DR2_API void LMLL_RxVGA2SetVga2G_u(int index);
CTR_6002DR2_API int LMLL_RxVGA2GetVga2G_u();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCCurrR(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCCurrR();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCDACB(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCDACB();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCCmpB(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCCmpB();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCDACA(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCDACA();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrDCCmpA(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrDCCmpA();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrBG(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrBG();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrBypAB(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrBypAB();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrBypB(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrBypB();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrBypA(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrBypA();

CTR_6002DR2_API void LMLL_RxVGA2SetPwrCurrRef(bool state);
CTR_6002DR2_API bool LMLL_RxVGA2GetPwrCurrRef();

CTR_6002DR2_API void LMLL_RxVGA2SetVga2GB_t(int index);
CTR_6002DR2_API int LMLL_RxVGA2GetVga2GB_t();

CTR_6002DR2_API void LMLL_RxVGA2SetVga2GA_t(int index);
CTR_6002DR2_API int LMLL_RxVGA2GetVga2GA_t();

CTR_6002DR2_API void LMLL_RxVGA2SetDCCalAddr(int index);
CTR_6002DR2_API int LMLL_RxVGA2GetDCCalAddr();

CTR_6002DR2_API void LMLL_RxVGA2SetVCM(int index);
CTR_6002DR2_API int LMLL_RxVGA2GetVCM();

CTR_6002DR2_API void LMLL_RxVGA2GetDCCalibrationData(int &calibVal, int &lockPattern, int &calibStatus, int &compValue);
//==============================================================================
// End of RxVGA2 Module

// RxFE Module
//==============================================================================
CTR_6002DR2_API char LMLL_RxFEGetAddr();

CTR_6002DR2_API void LMLL_RxFESetActiveLNA(int ind);
CTR_6002DR2_API void LMLL_RxFESelectInput(int ind);
CTR_6002DR2_API int LMLL_RxFEQueryInput(const char **description=NULL);

CTR_6002DR2_API void LMLL_RxFESetDecode(int index);
CTR_6002DR2_API int LMLL_RxFEGetDecode();

CTR_6002DR2_API void LMLL_RxFESetPwrRxFeMods(bool state);
CTR_6002DR2_API bool LMLL_RxFEGetPwrRxFeMods();

CTR_6002DR2_API void LMLL_RxFESetIN1SEL_MIX_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetIN1SEL_MIX_RXFE();

CTR_6002DR2_API void LMLL_RxFESetDCOFF_I_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetDCOFF_I_RXFE();

CTR_6002DR2_API void LMLL_RxFESetINLOAD_LNA_RXFE(bool state);
CTR_6002DR2_API bool LMLL_RxFEGetINLOAD_LNA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetDCOFF_Q_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetDCOFF_Q_RXFE();

CTR_6002DR2_API void LMLL_RxFESetXLOAD_LNA_RXFE(bool state);
CTR_6002DR2_API bool LMLL_RxFEGetXLOAD_LNA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetIP2TRIM_I_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetIP2TRIM_I_RXFE();

CTR_6002DR2_API void LMLL_RxFESetIP2TRIM_Q_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetIP2TRIM_Q_RXFE();

CTR_6002DR2_API void LMLL_RxFESetG_LNA_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetG_LNA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetLNASEL_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetLNASEL_RXFE();

CTR_6002DR2_API void LMLL_RxFESetCBE_LNA_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetCBE_LNA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetRFB_TIA_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetRFB_TIA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetCFB_TIA_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetCFB_TIA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetRDLEXT_LNA_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetRDLEXT_LNA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetRDLINT_LNA_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetRDLINT_LNA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetICT_MIX_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetICT_MIX_RXFE();

CTR_6002DR2_API void LMLL_RxFESetICT_LNA_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetICT_LNA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetICT_TIA_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetICT_TIA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetICT_MXLOB_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetICT_MXLOB_RXFE();

CTR_6002DR2_API void LMLL_RxFESetLOBN_MIX_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetLOBN_MIX_RXFE();

CTR_6002DR2_API void LMLL_RxFESetPD_TIA_RXFE(bool state);
CTR_6002DR2_API bool LMLL_RxFEGetPD_TIA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetPD_MXLOB_RXFE(bool state);
CTR_6002DR2_API bool LMLL_RxFEGetPD_MXLOB_RXFE();

CTR_6002DR2_API void LMLL_RxFESetPD_MIX_RXFE(bool state);
CTR_6002DR2_API bool LMLL_RxFEGetPD_MIX_RXFE();

CTR_6002DR2_API void LMLL_RxFESetPD_LNA_RXFE(bool state);
CTR_6002DR2_API bool LMLL_RxFEGetPD_LNA_RXFE();

CTR_6002DR2_API void LMLL_RxFESetRINEN_MIX_RXFE(bool state);
CTR_6002DR2_API bool LMLL_RxFEGetRINEN_MIX_RXFE();

CTR_6002DR2_API void LMLL_RxFESetG_FINE_LNA3_RXFE(int index);
CTR_6002DR2_API int LMLL_RxFEGetG_FINE_LNA3_RXFE();
//==============================================================================
// End of RxFE Module

// ADDC Module
// =============================================================================
CTR_6002DR2_API void LMLL_ADDCSetRX_FSYNC_P(int index);
CTR_6002DR2_API int LMLL_ADDCGetRX_FSYNC_P();

CTR_6002DR2_API void LMLL_ADDCSetRX_INTER(int index);
CTR_6002DR2_API int LMLL_ADDCGetRX_INTER();

CTR_6002DR2_API void LMLL_ADDCSetDAC_CLK_P(int index);
CTR_6002DR2_API int LMLL_ADDCGetDAC_CLK_P();

CTR_6002DR2_API void LMLL_ADDCSetTX_FSYNC_P(int index);
CTR_6002DR2_API int LMLL_ADDCGetTX_FSYNC_P();

CTR_6002DR2_API void LMLL_ADDCSetTX_INTER(int index);
CTR_6002DR2_API int LMLL_ADDCGetTX_INTER();

CTR_6002DR2_API void LMLL_ADDCSetEN_DAC(bool state);
CTR_6002DR2_API bool LMLL_ADDCGetEN_DAC();

CTR_6002DR2_API void LMLL_ADDCSetEN_ADC_DAC(bool state);
CTR_6002DR2_API bool LMLL_ADDCGetEN_ADC_DAC();

CTR_6002DR2_API void LMLL_ADDCSetEN_ADC_I(bool state);
CTR_6002DR2_API bool LMLL_ADDCGetEN_ADC_I();

CTR_6002DR2_API void LMLL_ADDCSetEN_ADC_Q(bool state);
CTR_6002DR2_API bool LMLL_ADDCGetEN_ADC_Q();

CTR_6002DR2_API void LMLL_ADDCSetEN_ADC_REF(bool state);
CTR_6002DR2_API bool LMLL_ADDCGetEN_ADC_REF();

CTR_6002DR2_API void LMLL_ADDCSetEN_M_REF(bool state);
CTR_6002DR2_API bool LMLL_ADDCGetEN_M_REF();

CTR_6002DR2_API void LMLL_ADDCSetBandgapTemp(int index);
CTR_6002DR2_API int LMLL_ADDCGetBandgapTemp();

CTR_6002DR2_API void LMLL_ADDCSetBandgapGain(int index);
CTR_6002DR2_API int LMLL_ADDCGetBandgapGain();

CTR_6002DR2_API void LMLL_ADDCSetRefAmpsBiasAdj(int index);
CTR_6002DR2_API int LMLL_ADDCGetRefAmpsBiasAdj();

CTR_6002DR2_API void LMLL_ADDCSetRefAmpsBiasUp(int index);
CTR_6002DR2_API int LMLL_ADDCGetRefAmpsBiasUp();

CTR_6002DR2_API void LMLL_ADDCSetRefAmpsBiasDn(int index);
CTR_6002DR2_API int LMLL_ADDCGetRefAmpsBiasDn();

CTR_6002DR2_API void LMLL_ADDCSetRefResistorBiasAdj(int index);
CTR_6002DR2_API int LMLL_ADDCGetRefResistorBiasAdj();

CTR_6002DR2_API void LMLL_ADDCSetRefBiasUp(int index);
CTR_6002DR2_API int LMLL_ADDCGetRefBiasUp();

CTR_6002DR2_API void LMLL_ADDCSetRefBiasDn(int index);
CTR_6002DR2_API int LMLL_ADDCGetRefBiasDn();

CTR_6002DR2_API void LMLL_ADDCSetRefGainAdj(int index);
CTR_6002DR2_API int LMLL_ADDCGetRefGainAdj();

CTR_6002DR2_API void LMLL_ADDCSetCoomonModeAdj(int index);
CTR_6002DR2_API int LMLL_ADDCGetCoomonModeAdj();

CTR_6002DR2_API void LMLL_ADDCSetRefBufferBoost(int index);
CTR_6002DR2_API int LMLL_ADDCGetRefBufferBoost();

CTR_6002DR2_API void LMLL_ADDCSetInputBufferDisable(bool state);
CTR_6002DR2_API bool LMLL_ADDCGetInputBufferDisable();

CTR_6002DR2_API void LMLL_ADDCSetADCSamplingPhase(int index);
CTR_6002DR2_API int LMLL_ADDCGetADCSamplingPhase();

CTR_6002DR2_API void LMLL_ADDCSetClockNonOverlapAdjust(int index);
CTR_6002DR2_API int LMLL_ADDCGetClockNonOverlapAdjust();

CTR_6002DR2_API void LMLL_ADDCSetADCBiasResistorAdjust(int index);
CTR_6002DR2_API int LMLL_ADDCGetADCBiasResistorAdjust();

CTR_6002DR2_API void LMLL_ADDCSetMainBiasDN(int index);
CTR_6002DR2_API int LMLL_ADDCGetMainBiasDN();

CTR_6002DR2_API void LMLL_ADDCSetADCAmp1Stage1BiasUp(int index);
CTR_6002DR2_API int LMLL_ADDCGetADCAmp1Stage1BiasUp();

CTR_6002DR2_API void LMLL_ADDCSetADCAmp24Stage1BiasUp(int index);
CTR_6002DR2_API int LMLL_ADDCGetADCAmp24Stage1BiasUp();

CTR_6002DR2_API void LMLL_ADDCSetADCAmp1Stage2BiasUp(int index);
CTR_6002DR2_API int LMLL_ADDCGetADCAmp1Stage2BiasUp();

CTR_6002DR2_API void LMLL_ADDCSetADCAmp24Stage2BiasUp(int index);
CTR_6002DR2_API int LMLL_ADDCGetADCAmp24Stage2BiasUp();

CTR_6002DR2_API void LMLL_ADDCSetQuantizerBiasUp(int index);
CTR_6002DR2_API int LMLL_ADDCGetQuantizerBiasUp();

CTR_6002DR2_API void LMLL_ADDCSetInputBufferBiasUp(int index);
CTR_6002DR2_API int LMLL_ADDCGetInputBufferBiasUp();

CTR_6002DR2_API void LMLL_ADDCSetDACInternalOutputLoadResistor(int index);
CTR_6002DR2_API int LMLL_ADDCGetDACInternalOutputLoadResistor();

CTR_6002DR2_API void LMLL_ADDCSetDACReferenceCurrentResistor(int index);
CTR_6002DR2_API int LMLL_ADDCGetDACReferenceCurrentResistor();

CTR_6002DR2_API void LMLL_ADDCSetDACFullScaleOutputCurrent(int index);
CTR_6002DR2_API int LMLL_ADDCGetDACFullScaleOutputCurrent();

CTR_6002DR2_API void LMLL_ADDCSetDecode(int index);
CTR_6002DR2_API int LMLL_ADDCGetDecode();
// =============================================================================
// End of ADDC Module

// FreqVsCap
// =============================================================================
CTR_6002DR2_API void LMLL_FreqVsCapSetVco(sVcoVsCap *sVco, int number, bool TxPLL);
CTR_6002DR2_API sVcoVsCap *LMLL_FreqVsCapGetVco(int number, bool TxPLL);
// =============================================================================
// End of FreqVsCap

// Board2 Module
//==============================================================================
CTR_6002DR2_API bool LMLL_BoardLoadRegValuesFromFile(char *FName);
CTR_6002DR2_API void LMLL_BoardConfigureSi5356A();
CTR_6002DR2_API void LMLL_BoardSetFrequency(unsigned int clkID, float refClkMHz, float ClockMHz);
CTR_6002DR2_API void LMLL_BoardSetClockInversion(unsigned int clkID, unsigned int inversion);
CTR_6002DR2_API void LMLL_BoardSetClockOutputFormat(unsigned int clkID, unsigned int format);
CTR_6002DR2_API void LMLL_BoardEnableClock(unsigned int clkID, bool clock_enabled);
CTR_6002DR2_API void LMLL_BoardSelectReferenceClk(bool CLKIN);

//==============================================================================
// End of Board2 Module

//==============================================================================
// Connection to chip interface
//==============================================================================
CTR_6002DR2_API int LMAL_SerialPortOnDeviceChange();
CTR_6002DR2_API int LMAL_SerialPortInitialize();
CTR_6002DR2_API int LMAL_Open();
CTR_6002DR2_API int LMAL_OpenI(unsigned int i);
CTR_6002DR2_API int LMAL_Close();
CTR_6002DR2_API bool LMAL_IsOpen();
CTR_6002DR2_API int LMAL_SetConnectionType(int Type);
CTR_6002DR2_API void LMAL_SPI_Rst();
CTR_6002DR2_API void LMAL_SPI_RstAct();
CTR_6002DR2_API void LMAL_SPI_RstInact();
CTR_6002DR2_API char LMAL_SPI_Read_OneByte(char Command);
CTR_6002DR2_API bool LMAL_SendData(const unsigned char *buffer, int &length);
CTR_6002DR2_API bool LMAL_ReadData(unsigned char *readCommands, int cmdCount, unsigned char *destBuffer, int &bytesRead);
CTR_6002DR2_API int LMAL_GetConnectionType();
CTR_6002DR2_API int LMAL_CurrentDevice();
CTR_6002DR2_API int LMAL_DeviceCount();
CTR_6002DR2_API void LMAL_DeviceName(char *name, int index);
CTR_6002DR2_API int LMAL_LoadSettings(const char *configFilename);
CTR_6002DR2_API int LMAL_SaveSettings(const char *configFilename);
CTR_6002DR2_API int LMAL_SetPortCustomParameter(char *paramName, char *value);
CTR_6002DR2_API int LMAL_GetPortCustomParameter(char *paramName, char *value);

//==============================================================================
// ADF Module
//==============================================================================
CTR_6002DR2_API void LMLL_ADF_SetFrefFvco(float Fref, float Fvco, int &rcount, int &ncount);
CTR_6002DR2_API void LMLL_ADF_SetReferenceCounterLatch(int Ldp, int Abw, int refCounter);
CTR_6002DR2_API void LMLL_ADF_SetNCounterLatch(int CPgain, int NCounter);
CTR_6002DR2_API void LMLL_ADF_SetFunctionLatch(int currentSetting1, int currentSetting2, int timerCounter, int fastLock, int muxoutControl);
CTR_6002DR2_API void LMLL_ADF_SetFunctionLatchRgr(int pdPol, int pd1, int pd2, int counterReset, int cpState);
CTR_6002DR2_API void LMLL_ADF_SetInitializationLatch(int currentSetting1, int currentSetting2, int timerCounter, int fastLock, int muxoutControl);
CTR_6002DR2_API void LMLL_ADF_SetInitializationLatchRgr(int pdPol, int pd1, int pd2, int counterReset, int cpState);
CTR_6002DR2_API void LMLL_ADF_SendConfig();

//==============================================================================
//End of ADF Module


// Testing Module
//==============================================================================
CTR_6002DR2_API void LMLL_Testing_GetSamples(float *Ich, float *Qch, int &IQsize, int &itemsLeft);
CTR_6002DR2_API void LMLL_Testing_GetFFTData(float *Ich, float *Qch, int &IQSize, float *FFTdataY, int &FFTsize, int &itemsLeft);
CTR_6002DR2_API void LMLL_Testing_SetCallbackUpdateInterface(void (*pCallbackFunction)(int, const char *));
CTR_6002DR2_API bool LMLL_Testing_CalculateFFT();

CTR_6002DR2_API void LMLL_Testing_StartSdramRead();
CTR_6002DR2_API void LMLL_Testing_StopSdramRead();
CTR_6002DR2_API void LMLL_Testing_ResetEndpoint();
CTR_6002DR2_API void LMLL_Testing_GetStatusInfo(unsigned long &bytesPs, unsigned int &failures);

CTR_6002DR2_API void LMLL_Testing_FPGAResetOn();
CTR_6002DR2_API void LMLL_Testing_FPGAResetOff();
CTR_6002DR2_API void LMLL_Testing_EnableFPGA(bool Tx, bool Rx);
CTR_6002DR2_API void LMLL_Testing_USBFIFOReset();

CTR_6002DR2_API void LMLL_Testing_SetRxDataSource(bool ADC);
CTR_6002DR2_API void LMLL_Testing_SetTxDataSource(bool FPGAtransmitter);
CTR_6002DR2_API void LMLL_Testing_SetDCCorrection(bool on);
CTR_6002DR2_API bool LMLL_Testing_SetFFTSamplesCount(unsigned int samplesCount);

// Support for RSS Integration
CTR_6002DR2_API void LMLL_Testing_SetFFTSpectra(float *FFTdataY, float *FFTdataX, int FFTsize, float FCenter);

//==============================================================================
// end of Testing Module

//Transmitter module
//==============================================================================
CTR_6002DR2_API void LMLL_Transmitter_StartSendingSamples();
CTR_6002DR2_API void LMLL_Transmitter_StopSendingSamples();
CTR_6002DR2_API void LMLL_Transmitter_GenerateSamples(double freqHz, double amplitude, double samplingRateHz);
CTR_6002DR2_API void LMLL_Transmitter_LoadSamplesFromFile(char *filename, bool binary);
CTR_6002DR2_API void LMLL_Transmitter_LoadSamplesFromArray(unsigned char*array, long length);
CTR_6002DR2_API void LMLL_Transmitter_GetSamples(float *Ichannel, float *Qchannel, int &samplesCount);
//==============================================================================
}
#endif

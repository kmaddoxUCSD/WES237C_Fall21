// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xfir.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XFir_CfgInitialize(XFir *InstancePtr, XFir_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XFir_Start(XFir *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL) & 0x80;
    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XFir_IsDone(XFir *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XFir_IsIdle(XFir *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XFir_IsReady(XFir *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XFir_Continue(XFir *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL) & 0x80;
    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XFir_EnableAutoRestart(XFir *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XFir_DisableAutoRestart(XFir *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_AP_CTRL, 0);
}

void XFir_Set_y(XFir *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_Y_DATA, (u32)(Data));
    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_Y_DATA + 4, (u32)(Data >> 32));
}

u64 XFir_Get_y(XFir *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_Y_DATA);
    Data += (u64)XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_Y_DATA + 4) << 32;
    return Data;
}

void XFir_Set_x(XFir *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_X_DATA, Data);
}

u32 XFir_Get_x(XFir *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_X_DATA);
    return Data;
}

void XFir_InterruptGlobalEnable(XFir *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_GIE, 1);
}

void XFir_InterruptGlobalDisable(XFir *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_GIE, 0);
}

void XFir_InterruptEnable(XFir *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_IER);
    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_IER, Register | Mask);
}

void XFir_InterruptDisable(XFir *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_IER);
    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_IER, Register & (~Mask));
}

void XFir_InterruptClear(XFir *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_WriteReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_ISR, Mask);
}

u32 XFir_InterruptGetEnabled(XFir *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_IER);
}

u32 XFir_InterruptGetStatus(XFir *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XFir_ReadReg(InstancePtr->Control_BaseAddress, XFIR_CONTROL_ADDR_ISR);
}


//
// Created by aeols on 2024-12-15.
//

#include "fsl_flexcan.h"

#include "MCXA_CAN_port.h"

namespace Platform
{
    const flexcan_config_t CAN0_config = {
        .bitRate = 1000000UL,
        .bitRateFD = 2000000UL,
        //            .clkSrc = kFLEXCAN_ClkSrcOsc,
        .wakeupSrc = kFLEXCAN_WakeupSrcUnfiltered,
        .maxMbNum = 16U,
        .enableLoopBack = false,
        .enableTimerSync = true,
        .enableSelfWakeup = false,
        .enableIndividMask = false,
        .disableSelfReception = false,
        .enableListenOnlyMode = false,
        .enableDoze = false,
        .enablePretendedeNetworking = false,
        .enableTransceiverDelayMeasure = true,
        .timingConfig = {
            .preDivider = 0,
            .rJumpwidth = 1,
            .phaseSeg1 = 3,
            .phaseSeg2 = 2,
            .propSeg = 0,
            .fpropSeg = 0,
        }
    };

    /* Message buffer 0 configuration structure */
    const flexcan_rx_mb_config_t CAN0_rx_mb_config_0 = {
        .id = FLEXCAN_ID_STD(0UL),
        .format = kFLEXCAN_FrameFormatStandard,
        .type = kFLEXCAN_FrameTypeData
    };

    void MCXA_CAN_port::initialize()
    {
        FLEXCAN_Init(CAN0, &CAN0_config, 8000000UL);
        /* Message buffer 0 initialization */
        FLEXCAN_SetRxMbConfig(CAN0, 0, &CAN0_rx_mb_config_0, true);
        /* Message buffer 1 initialization */
        FLEXCAN_SetTxMbConfig(CAN0, 1, true);
    }

    void MCXA_CAN_port::send_message(const CAN_message&)
    {
    }

    bool MCXA_CAN_port::receive_message(CAN_message&)
    {
        return false;
    }
} // Platform

/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief LPC84X ADC (DMA ��ʽ) �û������ļ�
 * \sa am_hwconf_lpc84x_adc0_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-14  hgo, add calibrate func
 * - 1.00 15-07-15  bob, first implementation
 * \endinternal
 */

#include <am_lpc84x.h>
#include "ametal.h"
#include "am_lpc84x_adc_dma.h"
#include "hw/amhw_lpc84x_clk.h"
#include "hw/amhw_lpc84x_adc.h"
#include "hw/amhw_lpc84x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc84x_adc0_dma
 * \copydoc am_hwconf_lpc84x_adc0_dma.c
 * @{
 */

/**
 * \brief ADC0 ƽ̨��ʼ��
 */
am_local void __lpc84x_adc0_dma_plfm_init (void)
{
    amhw_lpc84x_syscon_powerup(AMHW_LPC84X_SYSCON_PD_ADC0);
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_ADC);
    amhw_lpc84x_clk_adc_sel_set (AMHW_LPC84X_CLK_ADC_FRO, 1);

    /* ����ͨ������������Ϊ����ģʽ INACTIVE */
    am_gpio_pin_cfg(__ADC_IN0_PIN,  AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN1_PIN,  AM_LPC84X_GPIO_FUNC_OTHER2 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN2_PIN,  AM_LPC84X_GPIO_FUNC_OTHER2 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN3_PIN,  AM_LPC84X_GPIO_FUNC_OTHER2 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN4_PIN,  AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN5_PIN,  AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN6_PIN,  AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN7_PIN,  AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN8_PIN,  AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN9_PIN,  AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN10_PIN, AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);
    am_gpio_pin_cfg(__ADC_IN11_PIN, AM_LPC84X_GPIO_FUNC_OTHER1 | AM_GPIO_FLOAT);

    /* ADC �Զ����� */
    amhw_lpc84x_adc_calibrate(LPC84X_ADC0,
                              amhw_lpc84x_clk_system_clkrate_get());
}

/**
 * \brief ADC0 ƽ̨���ʼ��
 */
am_local void __lpc84x_adc0_dma_plfm_deinit (void)
{
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_ADC);
    amhw_lpc84x_syscon_powerdown(AMHW_LPC84X_SYSCON_PD_ADC0);
}

/** \brief ADC0 (DMA ��ʽ) �豸��Ϣ */
am_local am_const am_lpc84x_adc_dma_devinfo_t __g_lpc84x_adc0_dma_devinfo = {
    LPC84X_ADC0_BASE,                 /* ADC0 �Ĵ��������ַ */
    CLK_ADC,                          /* ADC0 ʱ�Ӻ� */
    2500,                             /* ADC �ο���ѹ����λ��mV */
    INUM_ADC0_SEQA,                   /* ADC0 ���� A �жϺ� */
    DMA_CHAN_0,                       /* ADC DMA ͨ�� 0 */
    __lpc84x_adc0_dma_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc84x_adc0_dma_plfm_deinit,    /* ƽ̨���ʼ������ */
};

/** \brief ADC0 (DMA ��ʽ) �豸ʵ�� */
am_local am_lpc84x_adc_dma_dev_t __g_lpc84x_adc0_dma_dev;

/**
 * \brief ADC0 (DMA ��ʽ) ʵ����ʼ��
 */
am_adc_handle_t am_lpc84x_adc0_dma_inst_init (void)
{
    return am_lpc84x_adc_dma_init(&__g_lpc84x_adc0_dma_dev,
                                  &__g_lpc84x_adc0_dma_devinfo);
}

/**
 * \brief ADC0 (DMA ��ʽ) ʵ�����ʼ��
 */
void am_lpc84x_adc0_dma_inst_deinit (am_adc_handle_t handle)
{
    am_lpc84x_adc_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */
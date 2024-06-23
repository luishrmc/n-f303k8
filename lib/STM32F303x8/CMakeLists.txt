set(HAL "${MCU}_HAL")
set(HAL_DRV "hal-driver/Src")

add_library(${HAL} STATIC)

target_sources(${HAL} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/Legacy/stm32f3xx_hal_can.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_adc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_adc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_can.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_cec.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_comp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_crc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_dac.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_dac_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_hrtim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_i2c_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_i2s.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_i2s_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_irda.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_iwdg.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_msp_template.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_nand.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_nor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_opamp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_opamp_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_pccard.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_pcd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_pcd_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_pwr_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_rtc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_rtc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_sdadc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_smartcard.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_smartcard_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_smbus.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_spi_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_sram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_tim.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_timebase_rtc_alarm_template.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_timebase_rtc_wakeup_template.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_timebase_tim_template.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_tsc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_uart_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_usart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_usart_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_hal_wwdg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_adc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_comp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_dac.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_fmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_hrtim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_opamp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_rtc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_usart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_usb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${HAL_DRV}/stm32f3xx_ll_utils.c
)

target_include_directories(${HAL} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/hal-driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/hal-driver/Inc/Legacy
)

target_compile_definitions(${HAL} PRIVATE
    ${MCU}
    USE_HAL_DRIVER
)

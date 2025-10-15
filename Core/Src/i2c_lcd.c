#include "i2c_lcd.h"
#include "i2c.h"

// --- 매핑 A: 가장 흔한 유형 (현재 코드 전제와 동일)
#define LCD_BL 0x08
#define LCD_EN 0x04
#define LCD_RW 0x02
#define LCD_RS 0x01
#define LCD_DATA_ON_UPPER_NIBBLE 1  // 데이터 D7..D4 = P7..P4

// --- 매핑 B: 일부 보드 (EN/RW가 뒤바뀌거나 데이터가 하위 4비트인 경우)
// #define LCD_BL 0x08
// #define LCD_EN 0x02
// #define LCD_RW 0x04
// #define LCD_RS 0x01
// #define LCD_DATA_ON_UPPER_NIBBLE 0  // 데이터 D7..D4 = P3..P0

// Function to initialize the LCD
void lcd_init(void)
{
    // 4-bit initialization

    HAL_Delay(50);  // Wait for >40ms
    lcd_send_cmd(0x30);
    HAL_Delay(5);   // Wait for >4.1ms
    lcd_send_cmd(0x30);
    HAL_Delay(1);   // Wait for >100us
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);  // 4-bit mode
    HAL_Delay(10);

    // Display initialization
    lcd_send_cmd(LCD_CMD_FUNCTION_SET);  // Function set: DL=0 (4-bit mode), N=1 (2-line display), F=0 (5x8 characters)
    HAL_Delay(1);
    lcd_send_cmd(LCD_CMD_DISPLAY_OFF);   // Display off
    HAL_Delay(1);
    lcd_send_cmd(LCD_CMD_CLEAR_DISPLAY); // Clear display
    HAL_Delay(2);
    lcd_send_cmd(LCD_CMD_ENTRY_MODE_SET); // Entry mode set: I/D=1 (increment cursor), S=0 (no shift)
    HAL_Delay(1);
    lcd_send_cmd(LCD_CMD_DISPLAY_ON);    // Display on: D=1, C=0, B=0 (Cursor and blink)
    HAL_Delay(1);
}

static HAL_StatusTypeDef lcd_write4(uint8_t nibble, uint8_t rs)
{
    // nibble은 상위4비트 자리에 D7..D4가 들어있다고 가정
    uint8_t data = (LCD_DATA_ON_UPPER_NIBBLE) ? (nibble & 0xF0) : ((nibble >> 4) & 0x0F);
    uint8_t base = data | LCD_BL | (rs ? LCD_RS : 0x00);
    uint8_t seq[2] = { base | LCD_EN, base }; // EN: High → Low 펄스
    return HAL_I2C_Master_Transmit(&hi2c1, (SLAVE_ADDRESS_LCD << 1), seq, 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef lcd_send_cmd(uint8_t cmd)
{
    if (lcd_write4(cmd & 0xF0, 0) != HAL_OK) return HAL_ERROR;
    if (lcd_write4(cmd << 4,    0) != HAL_OK) return HAL_ERROR;
    return HAL_OK;
}

HAL_StatusTypeDef lcd_send_data(uint8_t data)
{
    if (lcd_write4(data & 0xF0, 1) != HAL_OK) return HAL_ERROR;
    if (lcd_write4(data << 4,    1) != HAL_OK) return HAL_ERROR;
    return HAL_OK;
}

//
//// Function to send a command to the LCD
//HAL_StatusTypeDef lcd_send_cmd(uint8_t cmd)
//{
//	uint8_t data_u, data_l;
//    uint8_t data_t[4];
//
//    data_u = (cmd & 0xF0); // Upper nibble
//    data_l = ((cmd << 4) & 0xF0); // Lower nibble
//
//    data_t[0] = data_u | 0x0C; // Enable high, RS low
//    data_t[1] = data_u | 0x08; // Enable low, RS low
//    data_t[2] = data_l | 0x0C; // Enable high, RS low
//    data_t[3] = data_l | 0x08; // Enable low, RS low
//
//    if (HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD << 1, (uint8_t *)data_t, 4, HAL_MAX_DELAY) != HAL_OK)
//    {
//        // Handle error
//        return HAL_ERROR;
//    }
//    return HAL_OK;
//}
//
//// Function to send data to the LCD
//HAL_StatusTypeDef lcd_send_data(uint8_t data)
//{
//	uint8_t data_u, data_l;
//    uint8_t data_t[4];
//
//    data_u = (data & 0xF0); // Upper nibble
//    data_l = ((data << 4) & 0xF0); // Lower nibble
//
//    data_t[0] = data_u | 0x0D; // Enable high, RS high
//    data_t[1] = data_u | 0x09; // Enable low, RS high
//    data_t[2] = data_l | 0x0D; // Enable high, RS high
//    data_t[3] = data_l | 0x09; // Enable low, RS high
//
//    if (HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD << 1, (uint8_t *)data_t, 4, HAL_MAX_DELAY) != HAL_OK)
//    {
//        // Handle error
//        return HAL_ERROR;
//    }
//    return HAL_OK;
//}

// Function to clear the LCD screen
void lcd_clear(void)
{
    if (lcd_send_cmd(LCD_CMD_CLEAR_DISPLAY) != HAL_OK)
    {
        // Handle error
    }
    HAL_Delay(50); // Wait for the command to complete
}

// Function to set the cursor position on the LCD
void lcd_put_cursor(int row, int col)
{
    if (row == 0)
    {
        col |= LCD_CMD_SET_CURSOR; // Set position for row 0
    }
    else if (row == 1)
    {
        col |= (LCD_CMD_SET_CURSOR | 0x40); // Set position for row 1
    }

    lcd_send_cmd(col); // Send command to set cursor position
}

// Function to send a string to the LCD
void lcd_send_string(char *str)
{
    while (*str) lcd_send_data(*str++); // Send each character of the string
}

// Function to scan I2C addresses
uint8_t scan_i2c_address(void)
{
    HAL_StatusTypeDef result;
    uint8_t i;
    printf("Scanning I2C addresses...\n");
    for (i = 1; i < 128; i++)
    {
        result = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(i << 1), 1, 10);
        if (result == HAL_OK)
        {
            printf("I2C device found at address 0x%02X\n", i);
            return i;
        }
    }
    printf("No I2C devices found.\n");
    return 0;
}

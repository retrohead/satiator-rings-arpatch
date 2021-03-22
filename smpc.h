/** @brief force inline attribute (and prevent Doxygen prototype parsing bug) */
# define __force_inline                  __attribute__((always_inline)) inline

/** @brief SMPC Commands */
typedef enum
{
    /** @brief Resets and enables the SH-2 Master CPU. */
    EnableMasterCPU = 0x0,
    /** @brief Resets and enables the SH-2 Slave CPU. */
    EnableSlaveCPU = 0x2,
    /** @brief Disables the SH-2 Slave CPU. */
    DisableSlaveCPU = 0x3,
    /** @brief Resets and enables the Motorola C68K (sound) CPU. */
    EnableSoundCPU = 0x6,
    /** @brief Disables the Motorola C68K (sound) CPU. */
    DisableSoundCPU = 0x7,
    /** @brief Resets and enables the CD Block. */
    EnableCD = 0x8,
    /** @brief Disables the CD Block. */
    DisableCD = 0x9,
    /** @brief Resets and enables Netlink execution. */
    EnableNetlink = 0xA,
    /** @brief Disables Netlink execution. */
    DisableNetlink = 0xB,
    /** @brief 	Resets the System. */
    SystemReset = 0xD,
    /** @brief Changes the system clockspeed */
    ChangeSystemClockSpeed352 = 0xE,
    /** @brief Changes the system clockspeed */
    ChangeSystemClockSpeed320 = 0xF,
    /** @brief Fetches the SMPC status and peripheral data. */
    FetchStatusAndPeripheralData = 0x10,
    /** @brief Sets the date and time for the RTC */
    SetRTCDateAndTime = 0x16,
    /** @brief Sets the 4-byte battery-backed memory contained on the SMPC(which is used by the bios for language settings, etc. */
    SetSMPCMemory = 0x17,
    /** @brief Sends an NMI request to the Master SH2 */
    SendNMIRequestToMasterCPU = 0x18,
    /** @brief Enables NMI requests to be sent when the Reset button is pressed. */
    EnableReset = 0x19,
    /** @brief Disables NMI requests to be sent when the Reset button is pressed. */
    DisableReset = 0x1A
}               smpc_command;

typedef enum
{
    /** @brief The command that's supposed to be issued by the SMPC */
    CommandRegister = 0x2010001f,
    /** @brief Status Register */
    StatusRegister = 0x20100061,
    /** @brief Status Flag. Shows the status of the SMPC command. Normally you set this to 1 when issuing out a command, and then the SMPC clears it when it's finished. */
    StatusFlag = 0x20100063,
    /** @brief Input registers for command issuing. Whatever data the SMPC needs for processing command goes here. */
    InputRegister0 = 0x20100001,
    InputRegister1 = 0x20100003,
    InputRegister2 = 0x20100005,
    InputRegister3 = 0x20100007,
    InputRegister4 = 0x20100009,
    InputRegister5 = 0x2010000b,
    InputRegister6 = 0x2010000d,
    /** @brief Ouput Register for the command. If it supports it, it'll output any return data here */
    OutputRegister0 = 0x20100021,
    OutputRegister1 = 0x20100023,
    OutputRegister2 = 0x20100025,
    OutputRegister3 = 0x20100027,
    OutputRegister4 = 0x20100029,
    OutputRegister5 = 0x2010002b,
    OutputRegister6 = 0x2010002d,
    OutputRegister7 = 0x2010002f,
    OutputRegister8 = 0x20100031,
    OutputRegister9 = 0x20100033,
    OutputRegister10 = 0x20100035,
    OutputRegister11 = 0x20100037,
    OutputRegister12 = 0x20100039,
    OutputRegister13 = 0x2010003b,
    OutputRegister14 = 0x2010003d,
    OutputRegister15 = 0x2010003f,
    OutputRegister16 = 0x20100041,
    OutputRegister17 = 0x20100043,
    OutputRegister18 = 0x20100045,
    OutputRegister19 = 0x20100047,
    OutputRegister20 = 0x20100049,
    OutputRegister21 = 0x2010004b,
    OutputRegister22 = 0x2010004d,
    OutputRegister23 = 0x2010004f,
    OutputRegister24 = 0x20100051,
    OutputRegister25 = 0x20100053,
    OutputRegister26 = 0x20100055,
    OutputRegister27 = 0x20100057,
    OutputRegister28 = 0x20100059,
    OutputRegister29 = 0x2010005b,
    OutputRegister30 = 0x2010005d,
    OutputRegister31 = 0x2010005f,
    PortDataRegister1 = 0x20100075,
    PortDataRegister2 = 0x20100077,
    DataDirectionRegister1 = 0x20100079,
    DataDirectionRegister2 = 0x2010007b,
    InputOutputSelectRegister = 0x2010007d,
    ExternalLatchEnableRegister = 0x2010007f
}               smpc_memory_address;

static  __force_inline void smpc_write_byte(smpc_memory_address addr, unsigned char data)
{
    (*(volatile unsigned char *)(addr)) = data;
}
static  __force_inline unsigned char smpc_read_byte(smpc_memory_address addr)
{
    return (*(volatile unsigned char *)(addr));
}
static  __force_inline void smpc_wait(void)
{
    while ((smpc_read_byte(StatusFlag) & 0x1) == 0x1);
}
static  __force_inline void smpc_begin_command(void)
{
    smpc_wait();
    smpc_write_byte(StatusFlag, 1);
}
static  __force_inline void smpc_end_command(smpc_command command)
{
    smpc_write_byte(CommandRegister, command);
    smpc_wait();
}
static  __force_inline void restart_saturn(void)
{
    smpc_begin_command();
    smpc_end_command(SystemReset);
}

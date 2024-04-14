#include <iostream>
#include <windows.h>

int main() {
    // Mở cổng serial USB
    HANDLE hSerial = CreateFile("\\\\.\\COM3", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    }

    // Đặt cài đặt cổng serial
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Failed to get serial port parameters." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // Cài đặt tốc độ baudrate và các tham số khác nếu cần
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Failed to set serial port parameters." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // Đọc dữ liệu từ cổng serial
    DWORD bytesRead;
    char data[256]; // Độ dài dữ liệu cần đọc

    if (!ReadFile(hSerial, data, sizeof(data), &bytesRead, NULL)) {
        std::cerr << "Failed to read from serial port." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // Hiển thị dữ liệu đã đọc
    std::cout << "Received data: " << std::string(data, bytesRead) << std::endl;

    // Đóng cổng serial
    CloseHandle(hSerial);

    return 0;
}

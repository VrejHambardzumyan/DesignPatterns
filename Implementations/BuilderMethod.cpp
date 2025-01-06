#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class Computer;

class ComputerBuilder {
public:
    static ComputerBuilder create() {
        return ComputerBuilder();
    }

    ComputerBuilder& setCPU(const string& cpu) {
        m_cpu = cpu;
        return *this;
    }

    ComputerBuilder& setRAM(int ram) {
        m_ram = ram;
        return *this;
    }

    ComputerBuilder& setStorage(int storageSize, const string& type) {
        m_storage = to_string(storageSize);
        m_storageType = type;
        return *this;
    }

    ComputerBuilder& setGPU(const string& gpu) {
        m_gpu = gpu;
        return *this;
    }

    ComputerBuilder& addPeripheral(const string& peripheral) {
        m_peripherals.push_back(peripheral);
        return *this;
    }

    unique_ptr<Computer> build();

private:
    ComputerBuilder() = default;

    string m_cpu;
    int m_ram = 0;
    string m_storage;
    string m_storageType;
    string m_gpu;
    vector<string> m_peripherals;

    friend class Computer;
};


class Computer {
public:
    void showSpecs() const {
        cout << "Computer Specifications:" << endl;
        cout << "CPU: " << cpu << endl;
        cout << "RAM: " << ram << " GB" << endl;
        cout << "Storage: " << storage << " GB " << storageType << endl;
        cout << "GPU: " << (gpu.empty() ? "None" : gpu) << endl;
        
        cout << "Peripherals:" << endl;
        for (const auto& peripheral : peripherals) {
            cout << "- " << peripheral << endl;
        }
    }

private:

    Computer(const ComputerBuilder& builder) 
        : cpu(builder.m_cpu)
        , ram(builder.m_ram)
        , storage(builder.m_storage)
        , storageType(builder.m_storageType)
        , gpu(builder.m_gpu)
        , peripherals(builder.m_peripherals) 
    {}

    string cpu;
    int ram = 0;
    string storage;
    string storageType;
    string gpu;
    vector<string> peripherals;

    friend class ComputerBuilder;
};

unique_ptr<Computer> ComputerBuilder::build() {
   
    if (m_cpu.empty()) {
        throw runtime_error("CPU must be specified");
    }
    if (m_ram == 0) {
        throw runtime_error("RAM must be specified");
    }

    return unique_ptr<Computer>(new Computer(*this));
}

class ComputerDirector {
public:
    static unique_ptr<Computer> buildGamingComputer() {
        return ComputerBuilder::create()
            .setCPU("Intel Core i9")
            .setRAM(32)
            .setStorage(1000, "SSD")
            .setGPU("NVIDIA RTX 4090")
            .addPeripheral("Mechanical Keyboard")
            .addPeripheral("Gaming Mouse")
            .addPeripheral("Gaming Headset")
            .build();
    }

    static std::unique_ptr<Computer> buildOfficeComputer() {
        return ComputerBuilder::create()
            .setCPU("Intel Core i5")
            .setRAM(16)
            .setStorage(512, "SSD")
            .addPeripheral("Ergonomic Keyboard")
            .addPeripheral("Wireless Mouse")
            .build();
    }
};

int main() {
    cout << "Custom Computer:" << endl;
    auto customComputer = ComputerBuilder::create()
        .setCPU("AMD Ryzen 7")
        .setRAM(16)
        .setStorage(512, "NVMe SSD")
        .setGPU("AMD Radeon RX 6700")
        .addPeripheral("Wireless Keyboard")
        .addPeripheral("Bluetooth Mouse")
        .build();
    
    customComputer->showSpecs();

    cout << "\nGaming Computer:" << endl;
    auto gamingComputer = ComputerDirector::buildGamingComputer();
    gamingComputer->showSpecs();

    cout << "\nOffice Computer:" << endl;
    auto officeComputer = ComputerDirector::buildOfficeComputer();
    officeComputer->showSpecs();

}
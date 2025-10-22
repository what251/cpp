#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
using namespace std;
class Spaceship {
protected:
    string model;
    double speed;
    double energy;

public:
    Spaceship(string m, double s, double e) : model(m), speed(s), energy(e) {}
    virtual ~Spaceship() = default;
    virtual void showStats() const {
        cout << "�ͺ�: " << model
            << ", �ٶ�: " << speed
            << " ����/Сʱ, ����: " << energy << " ��λ";
    }
    virtual void action() = 0;
    string getModel() const { return model; }
    double getEnergy() const { return energy; }
    void setEnergy(double e) { energy = e; }
};
class CargoShip : public Spaceship {
private:
    double cargoCapacity;
    double currentCargo;

public:
    CargoShip(string m, double s, double e, double cap)
        : Spaceship(m, s, e), cargoCapacity(cap), currentCargo(0) {
    }

    void showStats() const override {
        cout << "[����ɴ�] ";
        Spaceship::showStats();
        cout << ", ��������: " << cargoCapacity
            << " ��, ��ǰ����: " << currentCargo << " ��";
    }

    void action() override {
        cout << "����ɴ� " << model << " ����װ�ػ���..." << endl;
    }
    void loadCargo(double cargo) {
        if (currentCargo + cargo <= cargoCapacity) {
            currentCargo += cargo;
            cout << "�ɹ�װ�� " << cargo << " �ֻ����ǰ����: "
                << currentCargo << "/" << cargoCapacity << " ��" << endl;
        }
        else {
            cout << "���󣺻��ﳬ�أ��������: " << cargoCapacity
                << " ��" << endl;
        }
    }
};
class BattleShip : public Spaceship {
private:
    double weaponPower;

public:
    BattleShip(string m, double s, double e, double wp)
        : Spaceship(m, s, e), weaponPower(wp) {
    }

    void showStats() const override {
        cout << "[ս���ɴ�] ";
        Spaceship::showStats();
        cout << ", ��������: " << weaponPower << " ��λ";
    }

    void action() override {
        cout << "ս���ɴ� " << model << " �������伤��..." << endl;
    }
    void fireLaser() {
        double energyCost = 15.0; 
        if (energy >= energyCost) {
            energy -= energyCost;
            cout << "���ⷢ�䣡����: " << weaponPower
                << " ��λ��ʣ������: " << energy << " ��λ" << endl;
        }
        else {
            cout << "�������㣡��Ҫ " << energyCost << " ��λ��������ǰֻ�� "
                << energy << " ��λ" << endl;
        }
    }
};
class ExplorerShip : public Spaceship {
private:
    double scanRange;

public:
    ExplorerShip(string m, double s, double e, double sr)
        : Spaceship(m, s, e), scanRange(sr) {
    }

    void showStats() const override {
        cout << "[̽���ɴ�] ";
        Spaceship::showStats();
        cout << ", ɨ�跶Χ: " << scanRange << " ����";
    }

    void action() override {
        cout << "̽���ɴ� " << model << " ����ɨ������..." << endl;
    }

    // ��ɫ������ɨ������
    void scanPlanet() {
        double energyCost = 10.0; // ÿ��ɨ������10��λ����
        if (energy >= energyCost) {
            energy -= energyCost;
            cout << "����ɨ����ɣ�ɨ�跶Χ: " << scanRange
                << " ���ꡣʣ������: " << energy << " ��λ" << endl;
        }
        else {
            cout << "�������㣡��Ҫ " << energyCost << " ��λ��������ǰֻ�� "
                << energy << " ��λ" << endl;
        }
    }
};
class SpaceshipFleet {
private:
    vector<unique_ptr<Spaceship>> ships;
    int cargoCount = 0;
    int battleCount = 0;
    int explorerCount = 0;

public:
    void showMenu() {
        cout << "\n===== �Ǽʷɴ�����ϵͳ =====" << endl;
        cout << "1. ���޷ɴ�" << endl;
        cout << "2. ���ӷɴ�" << endl;
        cout << "3. �鿴���зɴ�" << endl;
        cout << "4. �˳�ϵͳ" << endl;
        cout << "��ѡ�����: ";
    }
    void addShip() {
        cout << "\n----- ���ӷɴ� -----" << endl;
        cout << "ѡ��ɴ�����:" << endl;
        cout << "1. ����ɴ�" << endl;
        cout << "2. ս���ɴ�" << endl;
        cout << "3. ̽���ɴ�" << endl;
        cout << "��ѡ��: ";

        int type;
        cin >> type;

        string model;
        double speed, energy, special;

        cout << "�����ͺ�: ";
        cin >> model;
        cout << "�����ٶ�: ";
        cin >> speed;
        cout << "��������: ";
        cin >> energy;

        unique_ptr<Spaceship> newShip;

        switch (type) {
        case 1:
            cout << "�����������: ";
            cin >> special;
            newShip = make_unique<CargoShip>(model, speed, energy, special);
            cargoCount++;
            break;
        case 2:
            cout << "������������: ";
            cin >> special;
            newShip = make_unique<BattleShip>(model, speed, energy, special);
            battleCount++;
            break;
        case 3:
            cout << "����ɨ�跶Χ: ";
            cin >> special;
            newShip = make_unique<ExplorerShip>(model, speed, energy, special);
            explorerCount++;
            break;
        default:
            cout << "��Чѡ��" << endl;
            return;
        }

        ships.push_back(move(newShip));
        cout << "�ɴ���ӳɹ���" << endl;
    }
    void rentShip() {
        if (ships.empty()) {
            cout << "������û�зɴ���" << endl;
            return;
        }

        cout << "\n----- ���޷ɴ� -----" << endl;
        cout << "ѡ��Ҫ���޵ķɴ�:" << endl;

        for (size_t i = 0; i < ships.size(); i++) {
            cout << i + 1 << ". ";
            ships[i]->showStats();
            cout << endl;
        }

        cout << "��ѡ��ɴ����: ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > static_cast<int>(ships.size())) {
            cout << "��Чѡ��" << endl;
            return;
        }

        Spaceship* ship = ships[choice - 1].get();

        cout << "\n�������޷ɴ�..." << endl;
        ship->showStats();
        cout << endl;
        ship->action();
        if (auto cargoShip = dynamic_cast<CargoShip*>(ship)) {
            double cargo;
            cout << "����Ҫװ�صĻ�������: ";
            cin >> cargo;
            cargoShip->loadCargo(cargo);
        }
        else if (auto battleShip = dynamic_cast<BattleShip*>(ship)) {
            battleShip->fireLaser();
        }
        else if (auto explorerShip = dynamic_cast<ExplorerShip*>(ship)) {
            explorerShip->scanPlanet();
        }

        cout << "�ɴ�������ɣ�" << endl;
    }
    void viewAllShips() {
        cout << "\n----- ����ͳ�� -----" << endl;
        cout << "����ɴ�����: " << cargoCount << endl;
        cout << "ս���ɴ�����: " << battleCount << endl;
        cout << "̽���ɴ�����: " << explorerCount << endl;
        cout << "�ɴ�����: " << ships.size() << endl;

        if (!ships.empty()) {
            cout << "\n----- ���зɴ����� -----" << endl;
            for (size_t i = 0; i < ships.size(); i++) {
                cout << "�ɴ� " << i + 1 << ": ";
                ships[i]->showStats();
                cout << endl;
            }
        }
    }
    void run() {
        int choice;
        addExampleShips();

        do {
            showMenu();
            cin >> choice;

            switch (choice) {
            case 1:
                rentShip();
                break;
            case 2:
                addShip();
                break;
            case 3:
                viewAllShips();
                break;
            case 4:
                cout << "��лʹ���Ǽʷɴ�����ϵͳ��" << endl;
                break;
            default:
                cout << "��Чѡ�����������룡" << endl;
            }
        } while (choice != 4);
    }

private:
    void addExampleShips() {
        ships.push_back(make_unique<CargoShip>("CS-001", 120, 500, 1000));
        cargoCount++;
        ships.push_back(make_unique<BattleShip>("BS-001", 200, 300, 150));
        battleCount++;
        ships.push_back(make_unique<ExplorerShip>("ES-001", 180, 400, 50));
        explorerCount++;
        cout << "�Ѽ���ʾ���ɴ�..." << endl;
    }
};

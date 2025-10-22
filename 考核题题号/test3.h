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
        cout << "型号: " << model
            << ", 速度: " << speed
            << " 光年/小时, 能量: " << energy << " 单位";
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
        cout << "[运输飞船] ";
        Spaceship::showStats();
        cout << ", 货物容量: " << cargoCapacity
            << " 吨, 当前货物: " << currentCargo << " 吨";
    }

    void action() override {
        cout << "运输飞船 " << model << " 正在装载货物..." << endl;
    }
    void loadCargo(double cargo) {
        if (currentCargo + cargo <= cargoCapacity) {
            currentCargo += cargo;
            cout << "成功装载 " << cargo << " 吨货物。当前货物: "
                << currentCargo << "/" << cargoCapacity << " 吨" << endl;
        }
        else {
            cout << "错误：货物超载！最大容量: " << cargoCapacity
                << " 吨" << endl;
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
        cout << "[战斗飞船] ";
        Spaceship::showStats();
        cout << ", 武器威力: " << weaponPower << " 单位";
    }

    void action() override {
        cout << "战斗飞船 " << model << " 即将发射激光..." << endl;
    }
    void fireLaser() {
        double energyCost = 15.0; 
        if (energy >= energyCost) {
            energy -= energyCost;
            cout << "激光发射！威力: " << weaponPower
                << " 单位。剩余能量: " << energy << " 单位" << endl;
        }
        else {
            cout << "能量不足！需要 " << energyCost << " 单位能量，当前只有 "
                << energy << " 单位" << endl;
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
        cout << "[探索飞船] ";
        Spaceship::showStats();
        cout << ", 扫描范围: " << scanRange << " 光年";
    }

    void action() override {
        cout << "探索飞船 " << model << " 正在扫描星球..." << endl;
    }

    // 特色函数：扫描星球
    void scanPlanet() {
        double energyCost = 10.0; // 每次扫描消耗10单位能量
        if (energy >= energyCost) {
            energy -= energyCost;
            cout << "星球扫描完成！扫描范围: " << scanRange
                << " 光年。剩余能量: " << energy << " 单位" << endl;
        }
        else {
            cout << "能量不足！需要 " << energyCost << " 单位能量，当前只有 "
                << energy << " 单位" << endl;
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
        cout << "\n===== 星际飞船管理系统 =====" << endl;
        cout << "1. 租赁飞船" << endl;
        cout << "2. 增加飞船" << endl;
        cout << "3. 查看所有飞船" << endl;
        cout << "4. 退出系统" << endl;
        cout << "请选择操作: ";
    }
    void addShip() {
        cout << "\n----- 增加飞船 -----" << endl;
        cout << "选择飞船类型:" << endl;
        cout << "1. 运输飞船" << endl;
        cout << "2. 战斗飞船" << endl;
        cout << "3. 探索飞船" << endl;
        cout << "请选择: ";

        int type;
        cin >> type;

        string model;
        double speed, energy, special;

        cout << "输入型号: ";
        cin >> model;
        cout << "输入速度: ";
        cin >> speed;
        cout << "输入能量: ";
        cin >> energy;

        unique_ptr<Spaceship> newShip;

        switch (type) {
        case 1:
            cout << "输入货物容量: ";
            cin >> special;
            newShip = make_unique<CargoShip>(model, speed, energy, special);
            cargoCount++;
            break;
        case 2:
            cout << "输入武器威力: ";
            cin >> special;
            newShip = make_unique<BattleShip>(model, speed, energy, special);
            battleCount++;
            break;
        case 3:
            cout << "输入扫描范围: ";
            cin >> special;
            newShip = make_unique<ExplorerShip>(model, speed, energy, special);
            explorerCount++;
            break;
        default:
            cout << "无效选择！" << endl;
            return;
        }

        ships.push_back(move(newShip));
        cout << "飞船添加成功！" << endl;
    }
    void rentShip() {
        if (ships.empty()) {
            cout << "舰队中没有飞船！" << endl;
            return;
        }

        cout << "\n----- 租赁飞船 -----" << endl;
        cout << "选择要租赁的飞船:" << endl;

        for (size_t i = 0; i < ships.size(); i++) {
            cout << i + 1 << ". ";
            ships[i]->showStats();
            cout << endl;
        }

        cout << "请选择飞船编号: ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > static_cast<int>(ships.size())) {
            cout << "无效选择！" << endl;
            return;
        }

        Spaceship* ship = ships[choice - 1].get();

        cout << "\n正在租赁飞船..." << endl;
        ship->showStats();
        cout << endl;
        ship->action();
        if (auto cargoShip = dynamic_cast<CargoShip*>(ship)) {
            double cargo;
            cout << "输入要装载的货物数量: ";
            cin >> cargo;
            cargoShip->loadCargo(cargo);
        }
        else if (auto battleShip = dynamic_cast<BattleShip*>(ship)) {
            battleShip->fireLaser();
        }
        else if (auto explorerShip = dynamic_cast<ExplorerShip*>(ship)) {
            explorerShip->scanPlanet();
        }

        cout << "飞船租赁完成！" << endl;
    }
    void viewAllShips() {
        cout << "\n----- 舰队统计 -----" << endl;
        cout << "运输飞船数量: " << cargoCount << endl;
        cout << "战斗飞船数量: " << battleCount << endl;
        cout << "探索飞船数量: " << explorerCount << endl;
        cout << "飞船总数: " << ships.size() << endl;

        if (!ships.empty()) {
            cout << "\n----- 所有飞船详情 -----" << endl;
            for (size_t i = 0; i < ships.size(); i++) {
                cout << "飞船 " << i + 1 << ": ";
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
                cout << "感谢使用星际飞船管理系统！" << endl;
                break;
            default:
                cout << "无效选择，请重新输入！" << endl;
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
        cout << "已加载示例飞船..." << endl;
    }
};

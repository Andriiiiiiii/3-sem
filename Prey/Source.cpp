#include <iostream>
#include <string>
#include <Windows.h> // для русского языка
#include <cstdlib>
#include <ctime>
#include <math.h>



using namespace std;

typedef enum bebra {
	WEAPON,
	WRENCH,
	SIDEARM,
	SHOTGUN,
	PSYCHSHOCK,
} bebra;

int random(int b) { 
	int a;
	srand(time(NULL));
	a = rand() % b;
	return a;
}

class Weapon {
public:
	int DP; 
	bebra type = WEAPON;
	int ammo;
};

class Without_ammo :public Weapon{ 
public:
	Without_ammo(bool a) {
		if (a == true) { 
			type = WRENCH;
			DP = 35;
		}
		else { 
			type = PSYCHSHOCK;
			DP = 40;
		}
	}
};

class Firearm :public Weapon {
public:
	Firearm(bool a) {
		if (a == true) {
			type = SIDEARM;
			DP = 45;
			ammo = 7;                          
		}
		else {
			type = SHOTGUN;
			DP = 50;
			ammo = 5;
		}
	}
};

class Inventory {
public:
	unsigned int weapCount = 0; 
	Weapon** b = new Weapon * [10]; 
	bool check(bebra type) { 
		for (int i = 0; i < weapCount; i++) {
			if (b[i]->type == type) { return true; }
		}
		return false;
	}
	Weapon* get(bebra type) { 
		for (int i = 0; i < weapCount; i++) {
			if (b[i]->type == type) { return b[i]; }
		}
	}
	void add(Weapon* weapon) { 
		if (check(weapon->type)) { 
			get(weapon->type)->ammo+=3;
			delete weapon;
		}
		else {
			b[weapCount++] = weapon;
		}
	}
	~Inventory() {
		for (int i = 0; i < weapCount; i++) delete b[i]; 
		delete[] b;
	}
};

class Creature {
public:
	double HP;
	double DP;
	int n;
	string Name; 
	int points; 
	bool hweap; 
};

class Morgan : public Creature {
public:
	Inventory inventory;
	double AP;
	Morgan(string name) {
		hweap = false;
		HP = 100;
		AP = 100;
		DP = 25;
		Name = name;
		points = 0;
	}

};


int out_options(Morgan& a, int& wr, int& sd, int& shg, int& ps) {
	unsigned int at_type = 0;
	if (a.inventory.check(WRENCH)) {
		at_type++;
		cout << at_type << " - Атака гаечным ключом" << '\n';
		wr = at_type;
	}
	if (a.inventory.check(SIDEARM)) {
		if (a.inventory.get(SIDEARM)->ammo > 0) {
			at_type++;
			cout << at_type << " - Выстрел из пистолета. Осталось " << a.inventory.get(SIDEARM)->ammo << " патронов" << '\n';
			sd = at_type;
		}
		else cout << "В вашем верном пистолете не осталось патронов" << '\n';
	}
	if (a.inventory.check(SHOTGUN)) {
		if (a.inventory.get(SHOTGUN)->ammo > 0) {
			at_type++;
			cout << at_type << " - Выстрел из дробовика. Осталось " << a.inventory.get(SHOTGUN)->ammo << " патронов" << '\n';
			shg = at_type;
		}
		else cout << "Вы бы могли выстрелить из дробовика... если бы у вас были бы патроны" << '\n';
	}
	if (a.inventory.check(PSYCHSHOCK)) {
		at_type++;
		cout << at_type << " - Использовать Псишок" << '\n';
		ps = at_type;
	}
	return 0;
}

class Mimic :public Creature { 
public:
	static int kolvo_Mim;
	Mimic(int a) {
		n = a;
		HP = 47 + n * 3;
		DP = 10 + n * 3;
		Name = "Мимик";
		points = 90 + 5 * n;
	}
	virtual int attack(Morgan& a, int n) { 
		cout << a.Name << ": " << a.HP << '\n';
		cout << "Целостность брони: " << a.AP << "%" << '\n';
		cout << Name << ": " << HP << '\n' << '\n';
		int wr, ps;
		static int sd = -1, shg = -1;
		out_options(a, wr, sd, shg, ps);
		if (a.hweap) {
			bool flag = true; 
			int pl_ch;
			cin >> pl_ch;
			cout << '\n';
			while (flag) {
				if (pl_ch == wr) {
					HP -= a.inventory.get(WRENCH)->DP;
					break;
				}
				if (pl_ch == sd && sd != -1) {
					HP -= a.inventory.get(SIDEARM)->DP;
					a.inventory.get(SIDEARM)->ammo -= 1;
					if (a.inventory.get(SIDEARM)->ammo == 0) { sd = -1; }
					break;
				}
				if (pl_ch == shg && shg != -1) {
					HP -= a.inventory.get(SHOTGUN)->DP;
					a.inventory.get(SHOTGUN)->ammo -= 1;
					if (a.inventory.get(SHOTGUN)->ammo == 0) { shg = -1; }
					break;
				}
				if (pl_ch == ps) {
					HP -= a.inventory.get(PSYCHSHOCK)->DP;
					break;
				}
				cout << "Введите верную команду" << '\n';
				cin >> pl_ch;
			}
		}
		else HP -= a.DP;
		if (HP <= 0) { 
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "От трупа пришельца еще исходит еле уловимое тепло, однако признаков жизни он не подает" << '\n' << '\n';
			a.points += points;
			kolvo_Mim++;
			cout << "Из тела мимика торчит железная рукоятка. Она очень похожа на рукоятку от гаечного ключа." << '\n';
			cout << "Хотите ли взять гаечный ключ? 1-Да 2-Нет" << '\n';
			int choice=0;
			while (choice != 1 && choice != 2) {
				cin >> choice;
				cout << '\n';
				if (choice == 1) {
					if (a.inventory.check(WRENCH)) {
						cout << "Вы вытаскиваете железку из трупа. Да, это гаечный ключ... Точно такой же что и у вас... Он вам не нужен" << '\n' << '\n';
					}
					else {
						cout << "Вы со всей силой дергаете за рукоятку и она с неприятным звуком выходит из тела" << '\n';
						cout << "Это и в правду оказался гаечный ключ, вы решаете его оставить наслучай, если захотите 'починить' монстра" << '\n';
						cout << "Теперь вы можете использовать в качестве оружия гаечный ключ 'Гефест'!" << '\n' << '\n';
						a.inventory.add(new Without_ammo(true));
						a.hweap = true;
					}
					break;
				}
				if (choice == 2) {
					cout << "Вы решаете не рисковать, вдруг монстр еще жив и это ловушка. Вы уходите." << '\n' << '\n';
					break;
				}
				cout << "Дернуть за рукоятку? 1-Да, 2-Нет";
			}
			return 0;
		}
		if (a.AP > 0) { 
			a.HP -= DP * 0.2;
			a.AP -= DP * 0.75;
			if (a.AP < 0) { a.AP = 0; }
		}
		else { 
			a.HP -= DP;
		}

		if (a.HP <= 0) { 
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "Вы захлебываетесь собственной кровью, а лапы существа обхватывают вас все сильнее... " << '\n';
			cout << "В ваших глазах темнеет..." << '\n';
			cout << "Вы делаете свой последний вздох... " << '\n';
			return 0;
		}
		return attack(a, n);
	}
};

class Phantom :public Mimic {
public:
	static int kolvo_Phan; 
	double DC; 
	Phantom(int a) : Mimic(a) {
		n = a;
		HP = 95 + n * 5;
		DP = 20 + n * 5;
		Name = "Фантом";
		points = 140 + n * 10;
		DC = n * 0.05;
	}
	virtual int attack(Morgan& a, int n) override {
		cout << a.Name << ": " << a.HP << '\n';
		cout << "Целостность брони: " << a.AP << "%" << '\n';
		cout << Name << ": " << HP << '\n' << '\n';
		int wr, ps;
		static int sd = -1, shg = -1;
		out_options(a, wr, sd, shg, ps);
		if (a.hweap) {
			bool flag = true; 
			int pl_ch;
			cin >> pl_ch;
			cout << '\n';
			if (random(10) <= (DC * 10)) {
				cout << "С нечеловеческой скоростью пришелец, как будто бы неестественно, изгибает свое тело, уклоняясь от атаки не получая урона. Сразу же после этого он контратакует, вы тоже уворачиваетесь, хоть и не так эффективно  " << '\n' << '\n';;
				if (a.AP > 0) {
					a.HP -= DP * 0.2 * 0.8;
					a.AP -= DP * 0.75 * 0.8;
					if (a.AP < 0) { a.AP = 0; }
				}
				else { 
					a.HP -= DP * 0.8;
				}
				if (pl_ch == sd) a.inventory.get(SIDEARM)->ammo -= 1;
				if (pl_ch == shg) a.inventory.get(SHOTGUN)->ammo -= 1;
				if (a.HP <= 0) { 
					cout << a.Name << ": " << a.HP << '\n';
					cout << "Целостность брони: " << a.AP << "%" << '\n';
					cout << Name << ": " << HP << '\n' << '\n';
					cout << "Вы захлебываетесь собственной кровью, а лапы существа обхватывают вас все сильнее... " << '\n';
					cout << "В ваших глазах темнеет..." << '\n';
					cout << "Вы делаете свой последний вздох... " << '\n';
					return 0;
				}
				return attack(a, n);
			}
			else {
				while (flag) {
					if (pl_ch == wr) {
						HP -= a.inventory.get(WRENCH)->DP;
						break;
					}
					if (pl_ch == sd && sd != -1) {
						HP -= a.inventory.get(SIDEARM)->DP;
						a.inventory.get(SIDEARM)->ammo -= 1;
						if (a.inventory.get(SIDEARM)->ammo == 0) { sd = -1; }
						break;
					}
					if (pl_ch == shg && shg != -1) {
						HP -= a.inventory.get(SHOTGUN)->DP;
						a.inventory.get(SHOTGUN)->ammo -= 1;
						if (a.inventory.get(SHOTGUN)->ammo == 0) { shg = -1; }
						break;
					}
					if (pl_ch == ps) {
						HP -= a.inventory.get(PSYCHSHOCK)->DP;
						break;
					}
					if (flag) cout << "Введите верную команду" << '\n';
					cin >> pl_ch;
				}
			}
		}
		if (HP <= 0) { 
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "От трупа пришельца еще исходит еле уловимое тепло, однако признаков жизни он не подает" << '\n' << '\n';
			a.points += points;
			kolvo_Phan++;
			cout << "Из тела фантома торчит часть кобуры, возможно в ней еще остался пистолет." << '\n';
			cout << "Хотите взять кобуру? 1-Да, 2-Нет" << '\n';
			int choice = 0;
			while (choice != 1 && choice != 2) {
				cin >> choice;
				cout << '\n';
				if (choice == 1) {
					if (a.inventory.check(SIDEARM)) {
						cout << "Вы не боясь достаете из пришельца кобуру, из кобуры пистолет, а из пистолета патроны." << '\n' << '\n';
						a.inventory.add(new Firearm(true));
					}
					else {
						cout << "Вы хватаете кончик кобуры и тянете на себя, но фантом будто не хочет ее отдавать" << '\n';
						cout << "Однако, хорошо треснув по и так уже мертвому пришельцу кобура со служебным пистолетом попадает к вам в руки" << '\n';
						cout << "Теперь вы можете использовать в качестве оружия пистолет 'Трон ППН-8' !!" << '\n' << '\n';
						a.inventory.add(new Firearm(true));
						a.hweap = true;
					}
					break;
				}
				if (choice == 2) {
					cout << "Кобура почти вся в страшном пришельце, да и скорее всего прошлый владелец потратил весь боезопас. Вы уходите" << '\n' << '\n';
					break;
				}
				cout << "Вытащить кобуру? 1-Да, 2-Нет";
				}
			return 0;
		}
		if (a.AP > 0) {
			a.HP -= DP * 0.2;
			a.AP -= DP * 0.75;
			if (a.AP < 0) { a.AP = 0; }
		}
		else {
			a.HP -= DP;
		}
		if (a.HP <= 0) {
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "Вы захлебываетесь собственной кровью, а лапы существа обхватывают вас все сильнее... В ваших глазах темнеет... Вы делаете свой последний вздох... " << '\n';
			return 0;
		}
		return attack(a, n);
	}
};

class Thermal_Phantom : public Phantom {
public:
	static int kolvo_TPhan;
	Thermal_Phantom(int a) : Phantom(a) {
		n = a;
		HP = 95 + n * 7;
		DP = 30 + n * 5;
		Name = "Термофантом";
		points = 190 + n * 10;
		DC = 0.05 + n * 0.05;
	}
	int attack(Morgan& a, int n) override { 
		cout << a.Name << ": " << a.HP << '\n';
		cout << "Целостность брони: " << a.AP << "%" << '\n';
		cout << Name << ": " << HP << '\n' << '\n';
		int wr, ps;
		static int sd = -1, shg = -1;
		out_options(a, wr, sd, shg, ps);
		if (a.hweap) {
			bool flag = true;
			int pl_ch;
			cin >> pl_ch;
			cout << '\n';
			if (random(10) <= (DC * 10)) {
				cout << "С нечеловеческой скоростью пришелец, как будто бы неестественно, изгибает свое тело, уклоняясь от атаки не получая урона. Сразу же после этого он контратакует, вы тоже уворачиваетесь, хоть и не так эффективно  " << '\n' << '\n';
				if (a.AP > 0) {
					a.HP -= DP * 0.15 * 0.4;
					a.AP -= DP * 0.8 * 0.4;
					if (a.AP < 0) { a.AP = 0; }
				}
				else {
					a.HP -= DP * 0.5;
				}
				if (pl_ch == sd) a.inventory.get(SIDEARM)->ammo -= 1;
				if (pl_ch == shg) a.inventory.get(SHOTGUN)->ammo -= 1;
				if (a.HP <= 0) {
					cout << a.Name << ": " << a.HP << '\n';
					cout << "Целостность брони: " << a.AP << "%" << '\n';
					cout << Name << ": " << HP << '\n' << '\n';
					cout << "Вы чувтвуете как кровь в ваших жилах сворачивается " << '\n';
					cout << "В ваших глазах темнеет..." << '\n';
					cout << "Вы делаете свой последний вздох... " << '\n';
					return 0;
				}
				return attack(a, n);
			}
			else {
				while (flag) {
					if (pl_ch == wr) {
						HP -= a.inventory.get(WRENCH)->DP;
						break;
					}
					if (pl_ch == sd && sd != -1) {
						HP -= a.inventory.get(SIDEARM)->DP;
						a.inventory.get(SIDEARM)->ammo -= 1;
						if (a.inventory.get(SIDEARM)->ammo == 0) { sd = -1; }
						break;
					}
					if (pl_ch == shg && shg != -1) {
						HP -= a.inventory.get(SHOTGUN)->DP;
						a.inventory.get(SHOTGUN)->ammo -= 1;
						if (a.inventory.get(SHOTGUN)->ammo == 0) { shg = -1; }
						break;
					}
					if (pl_ch == ps) {
						HP -= a.inventory.get(PSYCHSHOCK)->DP;
						break;
					}
					if (flag) cout << "Введите верную команду" << '\n';
					cin >> pl_ch;
				}
			}
		}
		if (HP <= 0) {
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "От трупа пришельца еще исходит довольно уловимое тепло, однако признаков жизни он не подает" << '\n' << '\n';
			a.points += points;
			cout << "Из теплого тела красно-оранжевого фантома торчит кусок черного пластика, раз он не расплавился, значит это высококачественный пластик" << '\n';
			cout << "Может это приклад дробовика одного из офицеров охраны?" << '\n';
			cout << "Хотите вытащить кусок пластика? 1-Да, 2-Нет" << '\n';
			int choice = 0;
			while (choice != 1 && choice != 2) {
				cin >> choice;
				cout << '\n';
				if (choice == 1) {
					if ((a.inventory.check(SHOTGUN))) {
						cout << "Вы получаете патроны на дробовик и еще большее желание сходить в ледяной душ" << '\n' << '\n';
						a.inventory.add(new Firearm(false));
					}
					else {
						cout << "Вы хватаете кусок пластика, оперев одну ногу в пришельца, из монстра выходит струя горячего воздуха" << '\n';
						cout << "Вы делаете мощный рывок, и дробовик вылетает из термофантома, напоследок всадив в его лицо заряд дроби" << '\n';
						cout << "Теперь вы можете использовать в качестве оружия дробовик 'Трон Д4' !!" << '\n' << '\n';
						a.inventory.add(new Firearm(false));
						a.hweap = true;
					}
					break;
				}
				if (choice == 2) {
					cout << "Только от одного вида на эту груду мяса или чего бы это не было вам становится жарко. Вы уходите" << '\n' << '\n';
					break;
				}
				cout << "Вытащить кусок пластика? 1-Да, 2-Нет";
			}
			return 0;
		}
		if (a.AP > 0) {
			a.HP -= DP * 0.15;
			a.AP -= DP * 0.8;
			if (a.AP < 0) { a.AP = 0; }
		}
		else {
			a.HP -= DP;
		}
		if (a.HP <= 0) {
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "Вы захлебываетесь собственной кровью, а лапы существа обхватывают вас все сильнее... В ваших глазах темнеет... Вы делаете свой последний вздох... " << '\n';
			return 0;
		}
		return attack(a, n);
	}
};

class Voltaic_Phantom : public Phantom {
public:
	static int kolvo_VPhan;
	Voltaic_Phantom(int a) : Phantom(a) {
		n = a;
		HP = 95 + n * 5;
		DP = 30 + n * 5;
		Name = "Электрофантом";
		points = 190 + n * 10;
		DC = 0.05 + n * 0.05;
	}
	int attack(Morgan& a, int n) override {
		cout << a.Name << ": " << a.HP << '\n';
		cout << "Целостность брони: " << a.AP << "%" << '\n';
		cout << Name << ": " << HP << '\n' << '\n';
		int wr, ps;
		static int sd = -1, shg = -1;
		out_options(a, wr, sd, shg, ps);
		if (a.hweap) {
			bool flag = true;
			int pl_ch;
			cin >> pl_ch;
			cout << '\n';
			if (random(10) <= (DC * 10)) {
			cout << "С нечеловеческой скоростью пришелец, как будто бы неестественно, изгибает свое тело, уклоняясь от атаки не получая урона. Сразу же после этого он контратакует, вы тоже уворачиваетесь, хоть и не так эффективно  " << '\n' << '\n';
			if (a.AP > 0) {
				a.HP -= DP * 0.25 * 0.4;
				a.AP -= DP * 0.70 * 0.4;
				if (a.AP < 0) { a.AP = 0; }
			}
			else {
				a.HP -= DP * 0.5;
			}
			if (pl_ch == sd) a.inventory.get(SIDEARM)->ammo -= 1;
			if (pl_ch == shg) a.inventory.get(SHOTGUN)->ammo -= 1;
			if (a.HP <= 0) {
				cout << a.Name << ": " << a.HP << '\n';
				cout << "Целостность брони: " << a.AP << "%" << '\n';
				cout << Name << ": " << HP << '\n' << '\n';
				cout << "Вы захлебываетесь собственной кровью, а лапы существа обхватывают вас все сильнее... " << '\n';
				cout << "В ваших глазах темнеет..." << '\n';
				cout << "Вы делаете свой последний вздох... " << '\n';
				return 0;
			}
			return attack(a, n);
		}
			else {
				while (flag) {
					if (pl_ch == wr) {
						HP -= a.inventory.get(WRENCH)->DP;
						break;
					}
					if (pl_ch == sd && sd != -1) {
						HP -= a.inventory.get(SIDEARM)->DP;
						a.inventory.get(SIDEARM)->ammo -= 1;
						if (a.inventory.get(SIDEARM)->ammo == 0) { sd = -1; }
						break;
					}
					if (pl_ch == shg && shg != -1) {
						HP -= a.inventory.get(SHOTGUN)->DP;
						a.inventory.get(SHOTGUN)->ammo -= 1;
						if (a.inventory.get(SHOTGUN)->ammo == 0) { shg = -1; }
						break;
					}
					if (pl_ch == ps) {
						HP -= a.inventory.get(PSYCHSHOCK)->DP;
						break;
					}
					if (flag) cout << "Введите верную команду" << '\n';
					cin >> pl_ch;
				}
			}
		}
		if (HP <= 0) {
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "От трупа пришельца еще исходит еле уловимое тепло, однако признаков жизни он не подает" << '\n' << '\n';
			a.points += points;
			kolvo_VPhan++;
			cout << "Из светло-синего фантома торчит кусок черного пластика, вы слышите как из глубин тела исходит звук" << '\n';
			cout << "Такой звук издает неисправный привод дробовика" << '\n';
			cout << "Хотите вытащить кусок пластика? 1-Да, 2-Нет" << '\n';
			int choice = 0;
			while (choice != 1 && choice != 2) {
				cin >> choice;
				cout << '\n';
				if (choice == 1) {
					if ((a.inventory.check(SHOTGUN))) {
						cout << "Получив еще раз разряд тока, вы получаете несколько патронов на дробовик" << '\n' << '\n';
						a.inventory.add(new Firearm(false));
					}
					else {
						cout << "Вы хватаете кусок пластика, оперев одну ногу в пришельца, несмотря на то что подошвы ваших ботинок резиновые вы чувствуете как ток бежит по вашей коже" << '\n';
						cout << "Вы делаете мощный рывок, и дробовик вылетает из электрофантома, дробовик тут же перестает барахлить" << '\n';
						cout << "Теперь вы можете использовать в качестве оружия дробовик 'Трон Д4' !!" << '\n' << '\n';
						a.inventory.add(new Firearm(false));
						a.hweap = true;
					}
					break;
				}
				if (choice == 2) {
					cout << "Только от одного вида на эту груду мяса или чего бы это не было волосы на вашей голове элетризуются. Вы уходите" << '\n' << '\n';
					break;
				}
				cout << "Вытащить кусок пластика? 1-Да, 2-Нет";
			}
			return 0;
		}
		if (a.AP > 0) { 
			a.HP -= DP * 0.25;
			a.AP -= DP * 0.70;
			if (a.AP < 0) { a.AP = 0; }
		}
		else {
			a.HP -= DP * 1.05;
		}
		if (a.HP <= 0) {
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "Вы захлебываетесь собственной кровью, а лапы существа обхватывают вас все сильнее... В ваших глазах темнеет... Вы делаете свой последний вздох... " << '\n';
			return 0;
		}
		return attack(a, n);
	}
};

class Weaver :public Mimic {
public:
	static int kolvo_Weav;
	bool FAP;
	Weaver(int a) : Mimic(a) {
		HP = 120 + n * 5;
		DP = 10 + n * 20;
		Name = "Ткач";
		points = 240 + n * 10;
		FAP = true;
	}
	virtual int attack(Morgan& a, int n) {
		cout << a.Name << ": " << a.HP << '\n';
		cout << "Целостность брони: " << a.AP << "%" << '\n';
		cout << Name << ": " << HP << '\n' << '\n';
		int wr, ps;
		static int sd = -1, shg = -1;
		out_options(a, wr, sd, shg, ps);
		if (a.hweap) {
			bool flag = true;
			int pl_ch;
			cin >> pl_ch;
			cout << '\n';
			if (FAP == true) {
				cout << "атака не прошла" << '\n';
				FAP = false;
				if (pl_ch == sd) a.inventory.get(SIDEARM)->ammo -= 1;
				if (pl_ch == shg) a.inventory.get(SHOTGUN)->ammo -= 1;
				return attack(a, n);
			}
			while (flag) {
				if (pl_ch == wr) {
					HP -= a.inventory.get(WRENCH)->DP;
					break;
				}
				if (pl_ch == sd && sd != -1) {
					HP -= a.inventory.get(SIDEARM)->DP;
					a.inventory.get(SIDEARM)->ammo -= 1;
					if (a.inventory.get(SIDEARM)->ammo == 0) { sd = -1; }
					break;
				}
				if (pl_ch == shg && shg != -1) {
					HP -= a.inventory.get(SHOTGUN)->DP;
					a.inventory.get(SHOTGUN)->ammo -= 1;
					if (a.inventory.get(SHOTGUN)->ammo == 0) { shg = -1; }
					break;
				}
				if (pl_ch == ps) {
					HP -= a.inventory.get(PSYCHSHOCK)->DP;
					break;
				}
				cout << "Введите верную команду" << '\n';
				cin >> pl_ch;
			}
		}
		else HP -= a.DP;
		if (HP <= 0) {
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "От трупа пришельца еще исходит еле уловимое тепло, однако признаков жизни он не подает" << '\n' << '\n';
			a.points += points;
			kolvo_Weav++; 
			cout << "Из тела Ткача выходит мощный поток желтой энергии. Он так и манит вас" << '\n';
			cout << "Хотите ли подойти к источнику энергии? 1-Да 2-Нет" << '\n';
			int choice = 0;
			while (choice != 1 && choice != 2) {
				cin >> choice;
				cout << '\n';
				if (choice == 1) {
					if (a.inventory.check(PSYCHSHOCK)) {
						cout << "Вы заходите в луч чистой инопланетной энергии и-и-и-и... ничего не происходит" << '\n' <<'\n';
					}
					else {
						cout << "Сделав глубокий вдох вы заходите в луч космической мощи" << '\n';
						cout << "Лучи перенаправляются на вас, пронизывая кажду клеточку вашего тела, сияние пропадает, вас переполняет мощь!" << '\n';
						cout << "Теперь вы можете использовать в качестве оружия Псишок !!!" << '\n' << '\n';
						a.inventory.add(new Without_ammo(false));
						a.hweap = true;
					}
					break;
				}
				if (choice == 2) {
					cout << "Вы решаете не рисковать, вы и так за сегодня много чего повидали. Вы уходите." << '\n' << '\n';
					break;
				}
				cout << "Войти в луч энергии? 1-Да, 2-Нет";
			}
			return 0;
		}
		if (a.AP > 0) {
			a.HP -= DP * 0.2;
			a.AP -= DP * 0.75;
			if (a.AP < 0) { a.AP = 0; }
		}
		else {
			a.HP -= DP;
		}
		if (a.HP <= 0) {
			cout << a.Name << ": " << a.HP << '\n';
			cout << "Целостность брони: " << a.AP << "%" << '\n';
			cout << Name << ": " << HP << '\n' << '\n';
			cout << "Вы захлебываетесь собственной кровью, а лапы существа обхватывают вас все сильнее... " << '\n';
			cout << "В ваших глазах темнеет..." << '\n';
			cout << "Вы делаете свой последний вздох... " << '\n';
			return 0;
		}
		return attack(a, n);
	}
};

int Mimic::kolvo_Mim = 0;
int Phantom::kolvo_Phan = 0;
int Thermal_Phantom::kolvo_TPhan = 0;
int Voltaic_Phantom::kolvo_VPhan = 0;
int Weaver::kolvo_Weav = 0;

int game() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double n;
	string name;
	double ch;
	cout << "Введите свое имя: ";
	cin >> name;
	cout << "Введите уровень сложности: 1-Легкий, 2-Средний, 3-Сложный" << '\n';
	cin >> n;
	while (n < 1 || n>3 || n != floor(n)) {
		cout << '\n' << "Введена неправильная сложность" << '\n' << '\n';
		cout << "Введите уровень сложности: 1-Низкий, 2-Средний, 3-Высокий" << '\n';
		cin >> n;
	}
	cout << '\n';
	Morgan player(name);
	Mimic** a = new Mimic * [4 + 2 * n];
	int cur = 0;
	for (int i = 0; i < 4 + 2 * n; i++) {
		if (i==0){ a[i] = new Mimic(n); }
		else {
			switch (random(i + n)) { 
			case 0:                
			case 1:
				a[i] = new Mimic(n);
				break;
			case 2:
			case 3:
				a[i] = new Phantom(n);
				break;
			case 4:
			case 5:
				a[i] = new Thermal_Phantom(n);
				break;
			case 6:
			case 7:
				a[i] = new Voltaic_Phantom(n);
				break;
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
				a[i] = new Weaver(n);
				break;
			}
		}
		a[i]->attack(player, n); 
		cur++;
		if (player.HP <= 0) { 
			cout << "Вы умерли... \n Конец игры." << endl;
			for (int i = 0; i < cur; i++) delete a[i];
			delete[] a;
			return 0;
		}
		switch (random(10)) {
		case 0:
		case 1:
		case 2:
			cout << "Вы нашли аптечку! В ней содержится все, чтобы оказать первую помощь. Желаете ли её использовать? 1-Да, 2-Нет" << '\n';
			cin >> ch; 
			while (ch != 1 && ch != 2) {
				cout << "Желаете ли её использовать? 1-Да, 2-Нет" << '\n';
				cin >> ch;
			}
			if (ch == 1) {
				player.HP += 20 + n * 10;
			}
			break;
		case 3:
		case 4:
		case 5:
			cout << "Вы нашли Ремкомплект! С его помощью вы сможете залатать пару дыр в вашем костюме. Желаете ли его использовать? 1-Да, 2-Нет" << '\n';
			cin >> ch;
			while (ch != 1 && ch != 2) {
				cout << "Желаете ли его использовать? 1-Да, 2-Нет" << '\n';
				cin >> ch;
			}
			if (ch == 1) {
				player.AP += 20+n*10;
			}
			break;
		case 6:
		case 7:
		case 8:
			cout << "Вы нашли 'Набор Выживания' !! Открыв его вы видите две колбы со слабыми медикаментами и специнструмент, позволяющий исправить легкие неисправности костюма. Желаете ли использовать 'Набор Выживания'? 1-Да, 2-Нет" << '\n';
			cin >> ch;
			while (ch != 1 && ch != 2) {
				cout << "Желаете ли использовать 'Набор Выживания'? 1-Да, 2-Нет" << '\n';
				cin >> ch;
			}
			if (ch == 1) {
				player.AP += 20 + n * 10;
				player.HP += 20 + n * 10;
			}
			break;
			break;
		case 9:
			cout << "Вы нашли набор Доктора Феникса!!! Открыв его вы видите множество склянок со множеством различных лекарств и снадобий, а также кучу материалов с помощью которых можно сделать даже из самого порванного костюма полностью функционирующую броню. Желаете ли использовать набор Доктора Феникса? 1-Да, 2-Нет" << '\n';
			cin >> ch;
			while (ch != 1 && ch != 2) {
				cout << "Желаете ли использовать набор Доктора Феникса? 1-Да, 2-Нет" << '\n';
				cin >> ch;
			}
			if (ch == 1) {
				player.AP += 100;
				player.HP += 100;
			}
			break;
		}
	}
	cout << "Вы победили!! \n " << endl;
	cout << "Вы набрали " << player.points << " очков.";
	for (int i = 0; i < 4 + 2 * n; i++) delete a[i];
	delete[] a;
	return 0;
}

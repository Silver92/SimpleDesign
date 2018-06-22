#include <iostream>
#include <vector>
#include <string>

using namespace std;

//=========================================================================    
class Pizza {
public:
	string name;
	Dough dough;
	Sauce sauce;
	Veggies veggies[];
	Cheese cheese;
	Pepperoni pepperoni;
	Clams clam;

	virtual void prepare() = 0;

	void prepare() {
		cout << "prepare" << endl;
	}

	void bake() {
		cout << "bake" << endl;
	}

	void cut() {
		cout << "cut" << endl;
	}

	void box() {
		cout << "box" << endl;
	}

	string getName() {
		return name;
	}

	void setName(string s) {
		name = s;
	}
};

//=========================================================================
class CheesePizza: public Pizza {
PizzaIngredientFactory* ingredientFactory;

public:
	CheesePizza(PizzaIngredientFactory* ingredientFactory){
		this->ingredientFactory = ingredientFactory;
	}

	void prepare() {
		cout << "Preparing " << name << endl;
		dough = ingredientFactory->createDough();
		sauce = ingredientFactory->createSauce();
		cheese = ingredientFactory->createCheese();
	}
};

class ClamPizza: public Pizza {
PizzaIngredientFactory* ingredientFactory;

public:
	ClamPizza(PizzaIngredientFactory* ingredientFactory){
		this->ingredientFactory = ingredientFactory;
	}

	void prepare() {
		cout << "Preparing " << name << endl;
		dough = ingredientFactory->createDough();
		sauce = ingredientFactory->createSauce();
		cheese = ingredientFactory->createCheese();
		clam = ingredientFactory->createClam();
	}
};


// //=========================================================================
// class NYStyleCheesePizza: public Pizza {
// public: 
// 	NYStyleCheesePizza() {
// 		name = "NY Style Sauce and Cheese Pizza";
// 		dough = "Thin Crust Dough";
// 		sauce = "Marinara Sauce";

// 		toppings.push_back("Grated Reggiano Cheese");
// 	}

// };

// //=========================================================================    
// class NYStyleVeggiePizza: public Pizza {
// public: 
// 	NYStyleVeggiePizza() {
// 		name = "NY Style Sauce and Veggie Pizza";
// 		dough = "Thin Crust Dough";
// 		sauce = "Marinara Sauce";

// 		toppings.push_back("Grated Reggiano Cheese");
// 	}

// };

// //=========================================================================    
// class ChicagoStyleCheesePizza: public Pizza {
// public: 
// 	ChicagoStyleCheesePizza() {
// 		name = "Chicago Style Sauce and Cheese Pizza";
// 		dough = "Extra Thick Crust Dough";
// 		sauce = "Plum tomato Sauce";

// 		toppings.push_back("Shredded Mozzarella Cheese");
// 	}

// 	void cut() {
// 		cout << "Cutting the pizza into square slices." << endl;
// 	}

// };

//=========================================================================    
class PizzaIngredientFactory {
public:
	Dough createDough();
	Sauce createSauce();
	Cheese createCheese();
	Veggies[] createVeggies();
	Pepperoni createPepperoni();
	Clams createClam();
};

//=========================================================================    
class NYPizzaIngredientFactory: public PizzaIngredientFactory {
public:
	Dough createDough() {
		return new ThinCrustDough();
	}
	Sauce createSauce() {
		return new MarinaraSauce();
	}
	Cheese createCheese() {
		return new ReggianoCheese();
	}
	Veggies[] createVeggies() {
		Veggies veggies[] = {new Garlic(), new Onion(), new Mushroom, new RedPepper()};
		return veggies;
	}
	Pepperoni createPepperoni() {
		return new SlicedPepperoni();
	}
	Clams createClam() {
		return new FreshClams();
	}
};


//=========================================================================    
class PizzaStore{
public:
	Pizza* orderPizza(string type){
		Pizza* pizza;
		pizza = createPizza(type);

		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();

		return pizza;
	}

	virtual Pizza* createPizza(string type) = 0;
};

// //=========================================================================    
// class NYPizzaStore: public PizzaStore {
// 	Pizza* createPizza(string type) {
// 		if (type == "cheese") {
// 			return new NYStyleCheesePizza();
// 		} else if (type == "veggie") {
// 			return new NYStyleVeggiePizza();
// 		} else return nullptr;
// 	}
// };

class NYPizzaStore: public PizzaStore{
protected:
	Pizza* createPizza(string item) {
		Pizza pizza* = nullptr;
		PizzaIngredientFactory ingredientFactory = new NYPizzaIngredientFactory();
		if (item == "cheese") {
			pizza = new CheesePizza(ingredientFactory);
			pizza -> setName("New York Style Cheese Pizza");
		} else if (item = "clam") {
			pizza = new ClamPizza(ingredientFactory);
			pizza -> setName("New York Style Clam Pizza");
		}

		return pizza;
	}
}

//=========================================================================    
void placingOrder() {
	PizzaStore* nyPizzaStore = new NYPizzaStore();
	nyPizzaStore -> orderPizza("cheese");
}


int main() {
	placingOrder();

	return 0;
}









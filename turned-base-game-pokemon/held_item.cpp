#include <iostream>
#include <vector>
#include <string>
#include "held_item.hpp"

using namespace std;

HeldItem::HeldItem() {
    // Implement Here!
    name = "";
    isConsumable = false;
    isConsumed = false;
    effectType = "";
    effect = 0.0;
    conditionType = "";
    condition = "";
}

void HeldItem::displayInfo() const {
    cout  <<  "== Held Item Info ==\n";
    cout  << "Name: " << name << endl;
    cout  << "Consumable: " << (isConsumable ? "Yes" : "No") << endl;
    cout  << "Consumed: " << (isConsumed ? "Yes" : "No") << endl;
    cout  << "Effect Type: " << effectType << endl;
    cout  << "Effect: " << effect << endl;
    cout  << "Condition Type: " << conditionType << endl;
    cout  << "Condition: " << condition << endl;
    cout  << "====================\n";
    
}

void HeldItem::setName(const string& itemName) {
    // Implement Here!
    name = itemName;
}

string HeldItem::getName() const {
    // Implement Here!
    return name;
}

void HeldItem::setConsumable(bool itemConsumable) {
    // Implement Here!
    isConsumable = itemConsumable;
}

bool HeldItem::getConsumable() const {
    // Implement Here!
    return isConsumable;
    
}

void HeldItem::consumeItem() {
    // Implement Here!
    isConsumed = true;
}

bool HeldItem::getConsumed() const {
    // Implement Here!
    return isConsumed;
}

void HeldItem::setEffectType(const string& itemType) {
    // Implement Here!
    effectType = itemType;
}

string HeldItem::getEffectType() const {
    // Implement Here!
    return effectType;
}

void HeldItem::setEffect(double itemEffect) {
    // Implement Here!
    effect = itemEffect;
}

double HeldItem::getEffect() const {
    // Implement Here!
    return effect;
}

void HeldItem::setConditionType(const string& itemConditionType) {
    // Implement Here!
    conditionType = itemConditionType;
}

string HeldItem::getConditionType() const {
    // Implement Here!
    return conditionType;
}

void HeldItem::setCondition(const string& itemCondition) {
    // Implement Here!
    condition = itemCondition;
}

string HeldItem::getCondition() const {
    // Implement Here!
    return condition;
}
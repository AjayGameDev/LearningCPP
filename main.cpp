#include "Timer.h"
#include <cstdint>
#include <iostream>
#include <vector>

enum class Rarity : uint8_t
{
    Common,
    Frequent,
    Rare,
    RarityCount
};

struct Item
{
    uint32_t price = 1;
    bool stackable = false;
    std::string name = "default_item";
    Rarity rarity = Rarity::Common;

};

struct Item_Price
{
    uint8_t price = 1; // only takes 1 byte [0,255]
};

struct Item_Description
{
    bool stackable = false;
    std::string name = "default_item";
    Rarity rarity = Rarity::Common;
};

int main()
{
    std::vector<Item> items;
    std::vector<Item_Price> itemsPrices;
    std::vector<uint32_t> itemsPricesVector;

    constexpr uint32_t MAX_VALUE = 1000000;

    items.reserve(MAX_VALUE);
    itemsPrices.reserve(MAX_VALUE);
    itemsPricesVector.reserve(MAX_VALUE);

    for (int i = 0; i < MAX_VALUE; i++)
    {
        items.emplace_back();
        itemsPrices.emplace_back();
        itemsPricesVector.emplace_back(1);
    }

    uint32_t size_items = items.size() * sizeof(Item);
    uint32_t size_itemPrices = itemsPrices.size() * sizeof(Item_Price);
    uint32_t size_itemPricesVector = itemsPricesVector.size() * sizeof(uint32_t);

    Timer timer;
    uint32_t totalPrice = 0;

    
    timer.startTimer();

    for (const auto& item: items)
    {
        totalPrice += item.price;
    }

    timer.endTimer();

    std::cout << totalPrice << "\n";
    totalPrice = 0;

    timer.startTimer();

    for (const auto& itemPrice: itemsPrices)
    {
        totalPrice += itemPrice.price;
    }

    timer.endTimer();

    std::cout << totalPrice << "\n";
    totalPrice = 0;

    timer.startTimer();

    for (const auto& itemPrice: itemsPricesVector)
    {
        totalPrice += itemPrice;
    }

    timer.endTimer();

    std::cout << totalPrice << "\n";

    return 0;
}
#include <string>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

enum class CookieVariety
{
    ChocalateChip,
    Shortbread,
    Macaroon
};

class CookieOrder
{
public:
    using variety_type = CookieVariety;
    using num_boxes_type = int;

    CookieOrder(const variety_type& variety,
                num_boxes_type num_boxes) noexcept : variety_{variety},
                                                     num_boxes_{num_boxes} {}

    inline void variety(const variety_type& variety) noexcept
    {
        this->variety_ = variety;
    }
    inline variety_type variety() const noexcept
    {
        return this->variety_;    
    }
    inline void num_boxes(num_boxes_type num_boxes) noexcept
    {
        this->num_boxes_ = num_boxes;
    }
    inline num_boxes_type num_boxes() const noexcept
    {
        return this->num_boxes_;
    }
private:
    variety_type variety_;
    num_boxes_type num_boxes_;
};

using MasterOrder = std::vector<CookieOrder>;

CookieOrder::num_boxes_type total_box_count(const MasterOrder& master_order)
{
    return std::accumulate(master_order.begin(), master_order.end(), 0,
    [](CookieOrder::num_boxes_type num, const CookieOrder& order)
    {
        return num + order.num_boxes();
    });
}
CookieOrder::num_boxes_type variety_box_count(const MasterOrder& master_order,
                                              const CookieOrder::variety_type& variety)
{
    return std::accumulate(master_order.begin(), master_order.end(), 0,
    [&](CookieOrder::num_boxes_type num, const CookieOrder& order)
    {
        return num + (order.variety() == variety ? order.num_boxes() : 0);
    });
}

std::string to_string(CookieVariety variety)
{
    std::string variety_string;
    switch(variety)
    {
        case CookieVariety::ChocalateChip:
        {
            variety_string = "ChocalateChip";
            break;    
        }
        case CookieVariety::Shortbread:
        {
            variety_string = "Shortbread";
            break;
        }
        case CookieVariety::Macaroon:
        {
            variety_string = "Macaroon";
            break;
        }
    }
    return "CookieVariety::" + variety_string;
}

int main()
{
    MasterOrder order_list = {{CookieVariety::ChocalateChip, 1},
                              {CookieVariety::Shortbread, 5},
                              {CookieVariety::Macaroon, 2},
                              {CookieVariety::ChocalateChip, 3}};
    std::cout << "Total box count: " << total_box_count(order_list) <<std::endl;

    std::cout << "Total Chocolate Chip box count: "
              << variety_box_count(order_list, CookieVariety::ChocalateChip)
              << std::endl;

    auto new_end = std::remove_if(order_list.begin(),order_list.end(),
    [](const CookieOrder& order)
    {
        return order.variety() == CookieVariety::Macaroon;
    });
    order_list.erase(new_end, order_list.end());

    std::cout << "Total Macaroons: "
              << variety_box_count(order_list, CookieVariety::Macaroon)
              << std::endl;
    return 0;    
}
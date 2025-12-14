#pragma once
#include "sort_strategy.h"
#include <memory>
#include <stdexcept>

class SortContext {
  public:
    explicit SortContext(std::unique_ptr<SortStrategy> strategy)
        : m_strategy(std::move(strategy)) {
        if (!m_strategy)
            throw std::invalid_argument("SortContext requires a strategy");
    }

    void set_strategy(std::unique_ptr<SortStrategy> strategy) {
        if (!strategy)
            throw std::invalid_argument("Cannot set null strategy");
        m_strategy = std::move(strategy);
    }

    void sort(std::vector<int> &data) const {
        m_strategy->sort(data);
    }

    std::string strategy_name() const {
        return m_strategy->name();
    }

  private:
    std::unique_ptr<SortStrategy> m_strategy;
};

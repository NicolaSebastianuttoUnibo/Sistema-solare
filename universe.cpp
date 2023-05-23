#include "universe.hpp"
#include <cassert>
#include <numeric>

U::Universe::Universe(G::Newton const &newton) : newton_{newton} {}
int U::Universe::size() const
{
    return galaxy_.size();
}

void U::Universe::push_back(G::PlanetState const &ps) { galaxy_.push_back(ps); }
void U::Universe::evolve(double delta_t)
{
    assert(galaxy_.size() >= 1);
    copy_ = galaxy_;
    assert(copy_.size() == galaxy_.size());
    for (auto it = copy_.begin(); it < copy_.end(); ++it)
    {
        int idx = std::distance(copy_.begin(), it);
        double forzax_ = std::accumulate(copy_.begin(), copy_.end(), 0, [=](auto ci)
                                         { return newton_(it, ci).fx; });
        double forzay_ = std::accumulate(copy_.begin(), copy_.end(), 0, [=](auto ci)
                                         { return newton_(it, ci).fy; });
        galaxy_[idx] = solve(*it, forzax_, forzay_, delta_t);
    }
}
std::vector<G::PlanetState> const &U::Universe::state() const
{
    return galaxy_;
}
G::PlanetState U::Universe::solve(G::PlanetState const &ps, double fx, double fy, double delta_t) const
{
    double ax = fx / ps.m;
    double vx = ps.v_x + ax * delta_t;
    double x = ps.x + vx * delta_t + 0.5 * ax * delta_t * delta_t;

    double ay = fy / ps.m;
    double vy = ps.v_y + ay * delta_t;
    double y = ps.y + vy * delta_t + 0.5 * ay * delta_t * delta_t;

    G::PlanetState r{ps.m, x, y, vx, vy};
    return r;
}

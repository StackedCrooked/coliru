#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

class glicko;

struct match {
    enum : int {
        win, loss, tie
    };

    glicko* p1;
    glicko* p2;
    int result;

    double score() const noexcept {
        switch(result) {
        case match::win:
            return 1.0;
        case match::loss:
            return 0.0;
        case match::tie:
            return 0.5;
        default:
            return 0.0;
        }
    }
};

constexpr double pow2(double x) noexcept {
    return x * x;
}

// http://www.glicko.net/glicko/glicko2.pdf
class glicko {
public:
    static constexpr double tau = 0.5;
    static constexpr double pi = 3.141592653589793238463;
    static constexpr double scale = 173.7178;
    static constexpr double epsillon = 0.000001;
    glicko() noexcept = default;
    glicko(double r, double rdev = 350, double v = 0.06): vol(v) {
        rating(r);
        rd(rdev);
    }

    int rating() const noexcept {
        return static_cast<int>(scale * scaled_rating) + 1500;
    }

    void rating(int r) noexcept {
        scaled_rating = (r - 1500) / scale;
    }

    void rd(double arg) noexcept {
        scaled_rd = arg / scale;
    }

    double rd() const noexcept {
        return scale * scaled_rd;
    }

    double volatility() const noexcept {
        return vol;
    }

    void volatility(double v) noexcept {
        vol = v;
    }


    void update(const std::vector<match>& matches) {
        double v = calculate_v(matches);
        double scores = score_sum(matches);
        double delta = scores * v;
        double new_vol = new_volatility(delta, v);
        double pre_rating_period = std::sqrt(pow2(scaled_rd) + pow2(new_vol));
        double new_rd = 1 / std::sqrt(1/pow2(pre_rating_period) + 1/v);
        double new_rating = scaled_rating + pow2(new_rd) * scores;
        // actually update
        scaled_rating = new_rating;
        scaled_rd = new_rd;
        vol = new_vol;
    }
private:
    double scaled_rating = 0.0;
    double scaled_rd = 350 / scale;
    double vol = 0.06;

    // the g(o) function in Glicko-2
    double g(double op_rd) const noexcept {
        return 1 / std::sqrt(1 + (3 * pow2(op_rd))/pow2(pi));
    }

    // the E(micro, micro_j, o_j) function in Glicko-2
    // g_o is the result of g(opponent_vol) which could be pre-computed
    double E(double opponent_rating, double g_o) const noexcept {
        return 1 / (1 + std::exp(-g_o * (scaled_rating - opponent_rating)));
    }

    // step 3 to calculate quantity v
    double calculate_v(const std::vector<match>& matches) const noexcept {
        double sum = 0.0;
        for(auto&& match : matches) {
            if(match.p1 != this) {
                continue;
            }
            auto* opponent = match.p2;
            double g_o = g(opponent->scaled_rd);
            double e = E(opponent->scaled_rating, g_o);
            sum += pow2(g_o) * e * (1 - e);
        }
        return 1 / sum;
    }

    // part of step 4 and step 7 is to get the sum of scores
    double score_sum(const std::vector<match>& matches) const noexcept {
        double sum = 0.0;
        for(auto&& match : matches) {
            if(match.p1 != this) {
                continue;
            }
            auto* opponent = match.p2;
            double g_o = g(opponent->scaled_rd);
            double e = E(opponent->scaled_rating, g_o);
            sum += g_o * (match.score() - e);
        }
        return sum;
    }

    // the f(x) function in Glicko-2
    double f(double x, double delta, double v, double a) const noexcept {
        auto e = std::exp(x);
        double top = e * (pow2(delta) - pow2(scaled_rd) - v - e);
        double bottom = (pow2(scaled_rd) + v + e);
        bottom = 2 * pow2(bottom);
        return (top / bottom) - ((x - a) / pow2(tau));
    }

    // step 4 to calculate the new volatility
    double new_volatility(double delta, double v) const noexcept {
        double a = std::log(pow2(vol)); // ln(vol^2)
        double A = a;
        double B;
        if(pow2(delta) > (pow2(scaled_rd) + v)) {
            B = std::log(pow2(delta) - pow2(scaled_rd) - v);
        }
        else {
            int k = 1;
            for(; ;) {
                if(f(a - k * tau, delta, v, a) < 0.) {
                    ++k;
                    continue;
                }
                break;
            }
            B = a - k * tau;
        }

        double f_A = f(A, delta, v, a);
        double f_B = f(B, delta, v, a);
        while(std::abs(B - A) > epsillon) {
            double C = A + ((A - B) * f_A) / (f_B - f_A);
            double f_C = f(C, delta, v, a);
            if(f_C * f_B < 0.0) {
                A = B;
                f_A = f_B;
            }
            else {
                f_A /= 2;
            }
            B = C;
            f_B = f_C;
        }

        return std::exp(A / 2);
    }
};

int main() {
    // let's test this shit
    glicko player1(1500, 200);
    glicko player2(1400, 30);
    glicko player3(1550, 100);
    glicko player4(1700, 300);

    std::vector<match> matches = {
        { &player1, &player2, match::win },
        { &player1, &player3, match::loss },
        { &player1, &player4, match::loss }
    };

    player1.update(matches);
    std::cout << player1.rating() << '\n' << player1.rd() << '\n' << player1.volatility() << '\n';
}

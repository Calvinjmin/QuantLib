#include <ql/quantlib.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace QuantLib;

int main() {
    try {
        // Set up date and calendar
        Date today(1, Jan, 2024);
        Settings::instance().evaluationDate() = today;

        // Define bond parameters
        Natural settlementDays = 2; // Days until settlement
        Real faceAmount = 1000.0;   // Face value of the bond
        Rate couponRate = 0.05;      // 5% annual coupon rate
        Frequency frequency = Annual; // Annual coupon payment

        // Set up the schedule for the bond
        Date maturityDate(1, Jan, 2034);
        Schedule schedule(today, maturityDate, Period(frequency), NullCalendar(),
                          Unadjusted, Unadjusted, DateGeneration::Backward, false);

        // Create the fixed rate bond
        FixedRateBond bond(settlementDays, faceAmount, schedule,
                           vector<Rate>{couponRate}, Actual360());

        // Set up a yield curve (flat curve for simplicity)
        vector<Date> dates = {today, Date(1, Jan, 2025), Date(1, Jan, 2030), maturityDate};
        vector<Rate> rates = {0.04, 0.045, 0.05, 0.055}; // Example rates for the yield curve

        // Construct the yield curve
        Handle<YieldTermStructure> yieldCurve(
            boost::shared_ptr<YieldTermStructure>(
                new InterpolatedZeroCurve<Linear>(dates, rates, Actual360())));

        // Pricing engine
        boost::shared_ptr<PricingEngine> engine(
            new DiscountingBondEngine(yieldCurve));

        bond.setPricingEngine(engine);

        // Calculate and output the bond price
        Real bondPrice = bond.cleanPrice();
        cout << "The price of the bond is: " << bondPrice << endl;

        // Calculate and output the yield
        Rate bondYield = bond.yield(Actual360(), Compounded, Annual);
        cout << "The yield of the bond is: " << bondYield * 100 << "%" << endl;

    } catch (const QuantLib::Error& e) {
        cout << "QuantLib Error: " << e.what() << endl;
    } catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    } catch (...) {
        cout << "Unknown Exception caught!" << endl;
    }

    return 0;
}

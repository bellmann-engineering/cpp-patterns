#define BOOST_TEST_MODULE MoneyTest
#include <boost/test/included/unit_test.hpp>

#include "money.h" // project being tested
#include <string>

BOOST_AUTO_TEST_CASE(simple_add)
{
	// Arrange
    Money m12chf(12, "CHF");
    Money m14chf(14, "CHF");
    Money expected (26, "CHF");

	// act
    Money* observed = m12chf.add(m14chf);

	// assert
    BOOST_CHECK(expected == (*observed));
}

BOOST_AUTO_TEST_CASE(simple_add_with_different_currencies)
{
    Money m12chf(12, "EUR");
    Money m14chf(14, "USD");
    Money* observed = m12chf.add(m14chf);
	
    BOOST_CHECK(observed == NULL);
}

BOOST_AUTO_TEST_CASE(simple_add_expect_exception)
{
    Money m12chf(12, "EUR");
    Money m14chf(14, "USD");
	
    BOOST_CHECK_THROW(m12chf.add_with_ex(m14chf), std::invalid_argument);
}

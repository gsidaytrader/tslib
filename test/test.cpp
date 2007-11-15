#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/unit_test.hpp>
#include <ctime>
#include <tseries.hpp>

using namespace boost::unit_test_framework;

// seed random number generator
// srand((unsigned)time(0));

void null_constructor_test() {
  TSeries<double,double> x;

  // so we have the same type
  TSDIM zero = 0;
  BOOST_CHECK_EQUAL( x.nrow(), zero );
  BOOST_CHECK_EQUAL( x.ncol(), zero );
  BOOST_CHECK_EQUAL( x.getData(), static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getDates(), static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getColnames().size(), zero );
}

void std_constructor_test() {
  TSDIM nr = 1000;
  TSDIM nc = 10;
  TSDIM zero = 0;

  TSeries<double,double> x(nr,nc);

  BOOST_CHECK_EQUAL( x.nrow(), nr );
  BOOST_CHECK_EQUAL( x.ncol(), nc );
  BOOST_CHECK( x.getData() != static_cast<double*>(NULL) );
  BOOST_CHECK( x.getDates() != static_cast<double*>(NULL) );
  BOOST_CHECK_EQUAL( x.getColnames().size(), zero );
}

void set_colnames_test() {
  TSeries<double,double> x;

  vector<string> newColnames;

  newColnames.push_back("hat");
  newColnames.push_back("cat");

  // not allowed to set colnames not equal to number of cols
  BOOST_CHECK_EQUAL(x.setColnames(newColnames) , 1 );

  TSeries<double,double> y(100,2);

  // test set colnames success
  BOOST_CHECK_EQUAL(y.setColnames(newColnames) , 0 );

  // test that getColnames returns the correct value
  BOOST_CHECK_EQUAL(y.getColnames()==newColnames, 1);
}

void range_specifier_test() {

  vector<int> x;
  vector<int> y;

  x.push_back(1);
  x.push_back(2);
  x.push_back(3);
  x.push_back(4);
  x.push_back(5);

  y.push_back(1);
  y.push_back(3);
  y.push_back(5);

  RangeSpecifier<int,size_t> r(&x[0],&y[0],x.size(),y.size());

  BOOST_CHECK(r.getSize() == 3);
  BOOST_CHECK(r.getArg1()[0] == 0);
  BOOST_CHECK(r.getArg1()[1] == 2);
  BOOST_CHECK(r.getArg1()[2] == 4);
  
  BOOST_CHECK(r.getArg2()[0] == 0);
  BOOST_CHECK(r.getArg2()[1] == 1);
  BOOST_CHECK(r.getArg2()[2] == 2);
  
  r.print();
}

void operators_test() {
  TSDIM xnr = 100;
  TSDIM ynr = 10;
  TSDIM nc = 10;

  TSeries<double,double> x(xnr,nc);
  TSeries<double,double> y(ynr,nc);

  // gernate data
  fill_n(x.getData(),x.nrow()*x.ncol(),100.0);
  fill_n(y.getData(),y.nrow()*y.ncol(),1.0);

  // generate dates
  for(TSDIM xi = 0; xi < x.nrow(); xi++)
    x.getDates()[xi] = xi;

  // generate dates
  for(TSDIM yi = 0; yi < y.nrow(); yi++)
    y.getDates()[yi] = yi;
    
  TSeries<double,double> z = x + y;

  BOOST_CHECK_EQUAL( z.nrow(), y.nrow() );
  BOOST_CHECK_EQUAL( z.ncol(), 10 );
}


test_suite*
init_unit_test_suite( int argc, char* argv[] ) {
  test_suite* test= BOOST_TEST_SUITE("tslib test");

  test->add( BOOST_TEST_CASE( &null_constructor_test ) );
  test->add( BOOST_TEST_CASE( &std_constructor_test ) );
  test->add( BOOST_TEST_CASE( &set_colnames_test ) );
  
  test->add( BOOST_TEST_CASE( &range_specifier_test ) );
  test->add( BOOST_TEST_CASE( &operators_test ) );
  return test;
}

  

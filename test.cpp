#include "spreadsheet.hpp"
#include "select.hpp"

#include "gtest/gtest.h"


TEST(SelectionTest, SingleDataSheet){
	Spreadsheet testsheet;
	testsheet.set_column_names({"Animal"});
	testsheet.add_row({"monkey"});

	testsheet.set_selection(new Select_Contains(&testsheet, "Animal", ""));
	
	std::stringstream oss;
	testsheet.print_selection(oss);
	EXPECT_EQ(oss.str(), "monkey \n");
	oss.clear();
/**
	testsheet.set_selection(new Select_Contains(&testsheet, "Animal", "ant"));
	testsheet.print_selection(oss);
	EXPECT_EQ(oss.str(), "");
**/  
}


TEST(SelectionTest, MultipleCars){
	Spreadsheet testsheet;
	testsheet.set_column_names({"Vehicle", "Color"});
	testsheet.add_row({"cars", "red"});
	testsheet.add_row({"racecar", "green"});
	testsheet.add_row({"CAR", "yellow"}); 	

	testsheet.set_selection(new Select_Contains(&testsheet, "Vehicle", "car"));
	
	std::stringstream oss;
	testsheet.print_selection(oss);
	EXPECT_EQ(oss.str(), "cars red \nracecar green \n");
	oss.clear(); 
/**
	testsheet.set_selection(new Select_Contains(&testsheet, "Model", "car"));
	EXPECT_EQ(oss.str(), ""); 
**/ 
}
/**

TEST(SelectionTest, EmptyTest){
	Spreadsheet test;
	test.set_column_names({"First"});
	test.add_row({"Bob"});
	test.set_selection(new Select_Contains(&test, "Last", "Bob" ));
	
	std::stringstream oss;
	test.print_selection(oss);
	EXPECT_EQ(oss.str(), "");
}
**/ 

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

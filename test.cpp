#include "spreadsheet.hpp"
#include "select.hpp"

#include "gtest/gtest.h"


TEST(SelectionTest, NoSelection){
	Spreadsheet testsheet;
	testsheet.set_column_names({"Animal"});
	testsheet.add_row({"monkey"});

	testsheet.set_selection(new Select_Contains(&testsheet, "Animal", "ant"));

	std::stringstream oss; 
	testsheet.print_selection(oss);
	EXPECT_EQ(oss.str(), ""); 
	
	oss.str("");

	testsheet.set_selection(new Select_Contains(&testsheet, "Animal", "monkey")); 

	testsheet.print_selection(oss);
	EXPECT_EQ(oss.str(), "monkey \n");
}

TEST(SelectionTest, WrongData){
	Spreadsheet test;
	test.set_column_names({"Animal"});
	test.add_row({"cat"});
	test.set_selection(new Select_Contains(&test, "Animal", "ant"));
	
	std::stringstream oss;
	test.print_selection(oss);
	EXPECT_EQ(oss.str(), "");
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
}


TEST(SelectionTest, WrongColumnTest){
	Spreadsheet test;
	test.set_column_names({"First"});
	test.add_row({"Bob"});
	test.set_selection(new Select_Contains(&test, "Last", "Bob" ));
	
	std::stringstream oss;
	test.print_selection(oss);
	EXPECT_EQ(oss.str(), "");
}

TEST(SelectionTest, DuplicateCol){
	Spreadsheet test;
	test.set_column_names({"Class", "Class", "Major"});
	test.add_row({"English", "Freshman", "CS"});
	test.add_row({"History", "Senior", "Engineering"}); 
	test.set_selection(new Select_Contains(&test, "Class", "Freshman"));
	
	std::stringstream oss;
	test.print_selection(oss);
	EXPECT_EQ(oss.str(), "");

	oss.str("");

	test.set_selection(new Select_Or((new Select_Contains(&test,"Class", "History")), (new Select_Contains(&test, "Major", "CS")))); 
	test.print_selection(oss);
	EXPECT_EQ(oss.str(), "English Freshman CS \nHistory Senior Engineering \n"); 	

}

TEST(SelectionTest, AndTest){
	Spreadsheet test;
	test.set_column_names({"Last", "First"});
	test.add_row({"Doe", "Jane"});
	test.add_row({"Le", "Cody"});
	test.add_row({"Kim", "Zack"});
	test.set_selection(new Select_And((new Select_Contains(&test, "Last", "Le")), (new Select_Contains(&test, "First", "Zack"))));
	std::stringstream oss;
	test.print_selection(oss);
	EXPECT_EQ(oss.str(), "");
}

TEST(SelectionTest, Popsicles){
	Spreadsheet testsheet;
  	testsheet.set_column_names({"Flavor", "Color"});
  	testsheet.add_row({"strawberry", "red"});
  	testsheet.add_row({"cherry", "red"});
  	testsheet.add_row({"strawberry kiwi", "pink"});
  	testsheet.add_row({"watermelon", "pink"});
  	testsheet.add_row({"mango", "yellow"});
  	testsheet.add_row({"pineapple", "yellow"});
  	testsheet.add_row({"banana", "yellow"});
  	testsheet.add_row({"grape", "purple"});
  	std::stringstream oss;
  	testsheet.set_selection(new Select_Contains(&testsheet, "Flavor", "m"));
  	testsheet.print_selection(oss);
  	EXPECT_EQ(oss.str(), "watermelon pink \nmango yellow \n");
  	oss.str("");
  	testsheet.set_selection(new Select_Or(new Select_Contains(&testsheet, "Color", "red"), new Select_Not(new Select_Contains(&testsheet, "Color", "yellow"))));
  	testsheet.print_selection(oss);
  	EXPECT_EQ(oss.str(), "strawberry red \ncherry red \nstrawberry kiwi pink \nwatermelon pink \ngrape purple \n");
  	oss.str("");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

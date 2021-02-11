#include "spreadsheet.hpp"
#include "select.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    Spreadsheet library;
    library.set_column_names({"Title","Author_First","Author_Last","Genre"});
    library.add_row({"To Kill a Mockingbird","Harper","Lee","Fiction"});
    library.add_row({"Pride and Prejudice","Jane","Austin","Fiction"});
    library.add_row({"The Diary of a Young Girl","Anne","Frank","Non-Fiction"});
    library.add_row({"1984","George","Orwell","Fiction"});
    library.add_row({"Animal Farm","George","Orwell","Fiction"});
    library.add_row({"The Great Gatsby","F. Scott","Fitzgerald","Fiction"});
    library.add_row({"Into Thin Air","Jon","Krakauer","Non-Fiction"});

    library.print_selection(std::cout);
    std::cout << std::endl;

    library.set_selection(new Select_Not(new Select_Contains(&library,"Genre","Non-Fiction")));
    library.print_selection(std::cout);
    std::cout << std::endl;
    
    library.set_selection(
      new Select_Or(
        new Select_Contains(&library,"Author_Last","Lee"),
        new Select_Contains(&library,"Author_Last","Orwell")
      )
    );
    library.print_selection(std::cout);
    std::cout << std::endl;

    library.set_selection(
      new Select_And(
        new Select_Contains(&library,"Title","a"),
        new Select_Or(
          new Select_Contains(&library,"Title","The"),
          new Select_Contains(&library,"Author_Last","Austin")
        )
      )
    );
    library.print_selection(std::cout);
    std::cout << std::endl;

    return 0;
}

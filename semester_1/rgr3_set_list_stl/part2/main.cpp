#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>


struct Author {
    std::string surname_;
    std::string name_;
    std::string lastname_;

    bool operator<(const Author& other) const {
        if (surname_ == other.surname_) {
            if (name_ == other.name_) {
                return lastname_ < other.lastname_;
            }
            else {
                return name_ < other.name_;
            }
        }
        return surname_ < other.surname_;
    }

    void printAuthor() const {
        std::cout << surname_ << " " << name_ << " " << lastname_ << "\n";
    }

};      

struct Book {
    int udc;
    std::string title;
    int year;
    std::set<Author> authors; 

    bool operator<(const Book& other) const {
        return title < other.title;
    }

    void printBook() const {
        std::cout << "UDC #" << udc << "| Title: " << title << "| Publish year: " << year << " \n";
    }
};



class Library {
    private:
        std::set<Book> books;
		
    public:
        void addBook(const Book& book) {
            books.insert(book);
        }
        void deleteBook(const std::string title) {
            for (std::set<Book>::iterator it = books.begin(); it != books.end(); ++it) {
                if (it->title == title) {
                    books.erase(*it);
                    std::cout << title << " - this book was deleted from library\n";
                    break;
                }
            }
        }
        void searchBookByName(const std::string& title) {
            for(std::set<Book>::iterator it = books.begin(); it != books.end(); ++it)
                if (it->title == title) {
                    std::cout << title << " - This book is in library";
                    return;
                }
            std::cout << "Cant find "<< title <<" book in library";
        }
        void searchBooksByAuthor(const Author& author) {
            for (std::set<Book>::iterator it = books.begin(); it != books.end(); ++it) {
                if (it->authors.find(author) != it->authors.end()) {
                    std::cout << "Books of " << author.surname_ << " " << author.name_ << " " << author.lastname_ << " in library:\n";
                    it->printBook();
                    for (std::set<Author>::iterator ait = it->authors.begin(); ait != it->authors.end(); ++ait) {
                        ait->printAuthor();
                    }
                    
                }
            }
        }
        void addAuthorToBook(const std::string& title, const Author& author) {
            for (std::set<Book>::iterator it = books.begin(); it != books.end(); ++it) {
                if (it->title == title) {
                    Book updated = *it;
                    books.erase(it);
                    updated.authors.insert(author);
                    books.insert(updated);
                    std::cout << author.surname_ << " " << author.name_ << " " << author.lastname_ << " was added to authors of " << title << '\n';
                    return;
                }
            }
            std::cout << "Cant find " << title << " book";
        }

        void deleteAuthorFromBook(const std::string& title, const Author& author) {
            for (std::set<Book>::iterator it = books.begin(); it != books.end(); ++it) {
                if (it->title == title) {
                    Book updated = *it;
                    books.erase(it);
                    updated.authors.erase(author);
                    books.insert(updated);
                    std::cout << "Author: " << author.surname_ << " " << author.name_ << " " << author.lastname_ << " - deleted from authors of the " << title << "\n";
                    return;
                }
            }
            std::cout << "Cant find " << title << " book";
        }

        void loadBooksFromFile(const std::string& filename, Library& lib) {
            std::ifstream fin(filename);
            if (!(fin.is_open())) {
                throw std::runtime_error("Can't open input file");
            }
            if (fin.peek() == EOF) {
                throw std::runtime_error("Input file is empty");
            }
            while (true) {
                Book book;
                int authorCount;
                if (!(fin >> book.udc >> book.title >> book.year >> authorCount)) {
                    break;
                }
                std::replace(book.title.begin(), book.title.end(), '_', ' ');
                for (int i = 0; i < authorCount; ++i) {
                    Author a;
                    fin >> a.surname_ >> a.name_ >> a.lastname_;
                    book.authors.insert(a);

                }
                addBook(book);
            }    
            fin.close();
        }
        void printAllBooks() {
            for (std::set<Book>::iterator it = books.begin(); it != books.end(); ++it) {
                it->printBook();
                for (std::set<Author>::iterator ait = it->authors.begin(); ait != it->authors.end(); ++ait) {
                    ait->printAuthor();
                }
            }
        }
};


int main() {
    Library lib;
    try {
        lib.loadBooksFromFile("books.txt", lib);

        std::cout << "All books in library (sorted by title)\n";
        lib.printAllBooks();

        std::cout << "\n\nSearch book by name\n";
        lib.searchBookByName("War and Peace");

        std::cout << "\n\nSearch book by author (Pushkin)\n";
        Author pushkin{ "Pushkin", "Alexander", "Sergeevich" };
        lib.searchBooksByAuthor(pushkin);

        std::cout << "\n\nAdd author to book\n";
        Author newAuthor{ "Ivanov", "Ivan", "Ivanovich" };
        lib.addAuthorToBook("War and Peace", newAuthor);
        lib.searchBooksByAuthor(newAuthor);

        std::cout << "\n\nDelete author from book\n";
        lib.deleteAuthorFromBook("War and Peace", newAuthor);

        lib.searchBooksByAuthor(newAuthor);

        std::cout << "\n\nDelete book \n";
        lib.deleteBook("Poems and Verses");
        lib.searchBookByName("Poems and Verses");
        std::cout << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}




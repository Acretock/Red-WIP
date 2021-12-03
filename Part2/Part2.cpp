#include <string>
#include <list>
#include <string_view>
#include <iterator>
#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor() : cursor_iter(data.begin()) {}
    // сдвинуть курсор влево
    void Left() {
        if (cursor_iter != data.begin()) {
            cursor_iter--;
        }
    }
    // сдвинуть курсор вправо
    void Right() {
        if (cursor_iter != data.end()) {
            cursor_iter++;
        }
    }
    // вставить символ token
    void Insert(char token) {
        data.insert(cursor_iter, token); 
        if (cursor_iter != data.end()) {
            cursor_iter++;
        }
    }
    // cкопировать
    // не более tokens символов,
    // начиная с текущей позиции курсора
    void Copy(size_t tokens) {
        auto it = cursor_iter;
        for (size_t i = 0; i < tokens; i++) {
            buffer += *it;
            ++it;
        }
    }
    // вырезать не более tokens символов,
    // начиная с текущей позиции курсора
    void Cut(size_t tokens) {
        auto it = cursor_iter;
        for (size_t i = 0; i < tokens; i++) {
            buffer += *it;
            ++it;
        }
        data.erase(cursor_iter, it);
    }
    // вставить содержимое буфера
    // в текущую позицию курсора
    void Paste() {
        for (char c : buffer) {
            Insert(c);
        }
    }
    // получить текущее содержимое
    // текстового редактора
    string GetText() const {
        return {data.begin(),data.end()};
    }
private:
    list <char> data;
    string buffer;
    list<char>::iterator cursor_iter;
};

void TypeText(Editor& editor, const string& text) {
    for (char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        ASSERT_EQUAL(editor.GetText(), "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }

        // world
        editor.Cut(first_part_len);
        ASSERT_EQUAL(editor.GetText(), "world");
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        ASSERT_EQUAL(editor.GetText(), "world, ");
        // world,
        editor.Paste();
        // world, hello,_
        ASSERT_EQUAL(editor.GetText(), "world, hello, ");

        editor.Left();
        editor.Left();

        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for (char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}
void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
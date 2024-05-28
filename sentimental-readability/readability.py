from cs50 import get_string


def main():
    text = get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # print(letters)
    # print(words)
    # print(sentences)

    l = (letters * 100) / words
    s = (sentences * 100.0) / words
    grade = (0.0588 * l) - (0.296 * s) - 15.8

    # print(l)
    # print(s)
    # print(grade)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade " + str(round(grade)))


def count_letters(text):
    return float(len(text) - text.count(' ') - text.count('.') - text.count('!') - text.count('?') - text.count(',') - text.count("'"))


def count_words(text):
    return float(text.count(' ') + 1)


def count_sentences(text):
    return float(text.count('.') + text.count('!') + text.count('?'))


main()
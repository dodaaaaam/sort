assignment_04-1-(1)_P
import time


class Arr:
    def __init__(self, word, mean):
        self.word = word
        self.mean = mean

def print_arr(word_arr):
    for item in word_arr:
        print(f"{item.word} : {item.mean}")

def insertion_sort(word_arr):
    for i in range(1, len(word_arr)):
        word_arr[i].word = word_arr[i].word.lower()
        key = word_arr[i]
        j = i - 1
        while j >= 0 and key.word < word_arr[j].word:
            word_arr[j + 1] = word_arr[j]
            j -= 1
        word_arr[j + 1] = key

def main():
    try:
        with open("randdict_utf8.TXT", "r", encoding="utf-8") as file:
            word_arr = []
            for line in file:
                parts = line.strip().split(":")
                if len(parts) >= 2:
                    word = parts[0].strip()
                    mean = parts[1].strip()
                    word_arr.append(Arr(word, mean))
                elif len(parts) == 1:
                    word = parts[0].strip()
                    mean = ""
                    word_arr.append(Arr(word, mean))
    except FileNotFoundError:
        print("No file")
        return

    start_time = time.time()

    insertion_sort(word_arr)

    end_time = time.time()

    elapsed_time = end_time - start_time

    print("sorted array:")
    print_arr(word_arr)

    print(f"Execution time: {elapsed_time} seconds")

if __name__ == "__main__":
    main()
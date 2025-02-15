assignment_04-1-(2)
import time


class Arr:

    def __init__(self, word, mean):
        self.word = word
        self.mean = mean


def print_arr(word_arr):
    for item in word_arr:
        print(f"{item.word} : {item.mean}")


def adjust(word_arr, root, n):
    root_key = word_arr[root]
    root_index = root

    child = 2 * root + 1
    while child < n:
        if child + 1 < n and word_arr[child].word < word_arr[child + 1].word:
            child += 1
        if root_key.word >= word_arr[child].word:
            break
        word_arr[root_index] = word_arr[child]
        root_index = child
        child = 2 * root_index + 1
    word_arr[root_index] = root_key


def heap_sort(word_arr):
    n = len(word_arr)

    for i in range(n // 2 - 1, -1, -1):
        adjust(word_arr, i, n)

    for i in range(n - 1, 0, -1):
        word_arr[0], word_arr[i] = word_arr[i], word_arr[0]
        adjust(word_arr, 0, i)


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
    heap_sort(word_arr)
    end_time = time.time()

    elapsed_time = end_time - start_time

    print("Sorted array:")
    print_arr(word_arr)

    print(f"Execution time: {elapsed_time} seconds")


if __name__ == "__main__":
    main()

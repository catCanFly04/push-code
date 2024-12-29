#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
using namespace std;
using namespace std::chrono;

void display_array(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void display_graphics(const int arr[], int n, sf::RenderWindow &window, int current = -1, int min_index = -1) {
    window.clear(); // Clear the window for the next frame
    for (int i = 0; i < n; i++) {
        sf::RectangleShape rectangle(sf::Vector2f(20, arr[i] * 3)); // Rectangle height proportional to value
        rectangle.setPosition(50 + i * 25, 400 - arr[i] * 3);
        if (i == current) {
            rectangle.setFillColor(sf::Color::Red);
        } else if (i == min_index) {
            rectangle.setFillColor(sf::Color::Green);
        } else {
            rectangle.setFillColor(sf::Color::White);
        }
        window.draw(rectangle);
    }
    window.display(); // Update the window
    sf::sleep(sf::milliseconds(100)); // Add delay to slow down the sorting speed
}

void selection_sort(int arr[], int n, sf::RenderWindow &window, bool &reset_flag, int &operation_count, bool ascending, int &swap_count) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            operation_count++;
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    reset_flag = true;
                    return;
                }
            }
            if ((ascending && arr[j] < arr[min_index]) || (!ascending && arr[j] > arr[min_index])) {
                min_index = j;
            }
        }
        swap(arr[i], arr[min_index]);
        swap_count++;
        display_graphics(arr, n, window, i, min_index);
        cout << "Buoc " << i + 1 << ": ";
        display_array(arr, n);
        if (reset_flag) return;
    }
}

void insertion_sort(int arr[], int n, sf::RenderWindow &window, bool &reset_flag, int &operation_count, bool ascending, int &swap_count) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && ((ascending && arr[j] > key) || (!ascending && arr[j] < key))) {
            operation_count++;
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    reset_flag = true;
                    return;
                }
            }
            arr[j + 1] = arr[j];
            j = j - 1;
            swap_count++;
        }
        arr[j + 1] = key;
        display_graphics(arr, n, window, j + 1, i);
        cout << "Buoc " << i << ": ";
        display_array(arr, n);
        if (reset_flag) return;
    }
}

void bubble_sort(int arr[], int n, sf::RenderWindow &window, bool &reset_flag, int &operation_count, bool ascending, int &swap_count) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            operation_count++;
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    reset_flag = true;
                    return;
                }
            }
            if ((ascending && arr[j] > arr[j + 1]) || (!ascending && arr[j] < arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
                swap_count++;
            }
        }
        display_graphics(arr, n, window, -1, -1); // Cập nhật đồ họa sau mỗi lần lặp
        cout << "Buoc " << i + 1 << ": ";
        display_array(arr, n);
        if (reset_flag) return;
    }
}

void run_sorting_algorithm(void (*sort_func)(int[], int, sf::RenderWindow&, bool&, int&, bool, int&), int arr[], int n, sf::RenderWindow &window, const string &name, bool ascending) {
    int operation_count = 0;
    int swap_count = 0;
    bool reset_flag = false;
    auto start = high_resolution_clock::now();
    sort_func(arr, n, window, reset_flag, operation_count, ascending, swap_count);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << name << " - Time: " << duration << " ms, Comparisons: " << operation_count << ", Swaps: " << swap_count << endl;
}

int main() {
    int n;
    cout << "Nhap so phan tu: ";
    cin >> n;
    int initial_arr[n];
    cout << "Nhap cac phan tu: ";
    for (int i = 0; i < n; i++) {
        cin >> initial_arr[i];
    }
    char order_choice;
    cout << "Sap xep tang dan (T) hay giam dan (G)? ";
    cin >> order_choice;
    bool ascending = (order_choice == 'T' || order_choice == 't');

    int arr[n];
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Algorithms Comparison");
    window.setFramerateLimit(60); // Giới hạn tốc độ khung hình để không quá tải
    while (window.isOpen()) {
        for (int i = 0; i < n; i++) {
            arr[i] = initial_arr[i];
        }
        cout << "Mang truoc khi sap xep: ";
        display_array(arr, n);
        display_graphics(arr, n, window);

        cout << "Running Selection Sort..." << endl;
        run_sorting_algorithm(selection_sort, arr, n, window, "Selection Sort", ascending);

        for (int i = 0; i < n; i++) {
            arr[i] = initial_arr[i];
        }
        cout << "Running Insertion Sort..." << endl;
        run_sorting_algorithm(insertion_sort, arr, n, window, "Insertion Sort", ascending);

        for (int i = 0; i < n; i++) {
            arr[i] = initial_arr[i];
        }
        cout << "Running Bubble Sort..." << endl;
        run_sorting_algorithm(bubble_sort, arr, n, window, "Bubble Sort", ascending);

        // Exit the program after completing the three sorting algorithms
        window.close();
        break;
    }

    return 0;
}

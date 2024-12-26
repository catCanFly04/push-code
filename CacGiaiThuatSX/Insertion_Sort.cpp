#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

void display_array(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void display_graphics(const int arr[], int n, sf::RenderWindow &window, int current = -1, int key_index = -1) {
    window.clear();
    for (int i = 0; i < n; i++) {
        sf::RectangleShape rectangle(sf::Vector2f(20, arr[i] * 3));
        rectangle.setPosition(50 + i * 25, 400 - arr[i] * 3);
        if (i == current) {
            rectangle.setFillColor(sf::Color::Red); // Highlight current element
        } else if (i == key_index) {
            rectangle.setFillColor(sf::Color::Green); // Highlight key element
        } else {
            rectangle.setFillColor(sf::Color::White);
        }
        window.draw(rectangle);
    }
    window.display();
}

void insertion_sort(int arr[], int n, sf::RenderWindow &window, bool &reset_flag) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            // Xử lý sự kiện để cửa sổ không bị treo và kiểm tra reset
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

            // Hiển thị trạng thái mảng
            display_graphics(arr, n, window, j + 1, i);
            sf::sleep(sf::milliseconds(1000)); // Dừng để nhìn thấy sự so sánh

            if (reset_flag) return;
        }
        arr[j + 1] = key;

        // Hiển thị sau khi chèn
        display_graphics(arr, n, window, j + 1, i);
        sf::sleep(sf::milliseconds(1000)); // Dừng để nhìn thấy sự chèn

        // In mảng ra console sau mỗi bước
        cout << "Buoc " << i << ": ";
        display_array(arr, n);

        if (reset_flag) return;
    }
}

int main() {
    int initial_arr[] = {64, 25, 12, 22, 11, 90, 45, 33, 77, 55};
    int n = sizeof(initial_arr) / sizeof(initial_arr[0]);
    int arr[10];

    sf::RenderWindow window(sf::VideoMode(800, 600), "Insertion Sort Visualization");

    while (window.isOpen()) {
        // Copy mảng gốc vào mảng hiện tại
        for (int i = 0; i < n; i++) {
            arr[i] = initial_arr[i];
        }

        // Hiển thị mảng ban đầu
        cout << "Mang truoc khi sap xep: ";
        display_array(arr, n);

        bool reset_flag = false;

        // Hiển thị trạng thái ban đầu
        display_graphics(arr, n, window);
        sf::sleep(sf::milliseconds(1000)); // Dừng để nhìn thấy trạng thái ban đầu

        // Khởi động thuật toán sắp xếp và cho phép reset
        insertion_sort(arr, n, window, reset_flag);

        // Hiển thị mảng đã sắp xếp nếu không reset
        if (!reset_flag) {
            cout << "Mang sau khi sap xep: ";
            display_array(arr, n);

            display_graphics(arr, n, window);
            sf::sleep(sf::milliseconds(1000)); // Dừng để nhìn thấy trạng thái cuối cùng
        }

        // Vòng lặp sự kiện để giữ cửa sổ mở hoặc reset
        while (window.isOpen() && !reset_flag) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    reset_flag = true; // Reset quá trình
                }
            }
        }
    }

    return 0;
}
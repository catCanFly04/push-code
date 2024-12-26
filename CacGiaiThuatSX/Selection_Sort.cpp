#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

// Hàm in mảng ra console
void display_array(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Hàm hiển thị mảng dưới dạng đồ họa
void display_graphics(const int arr[], int n, sf::RenderWindow &window, int current = -1, int min_index = -1) {
    window.clear(); // Xóa màn hình trước khi vẽ lại
    for (int i = 0; i < n; i++) {
        sf::RectangleShape rectangle(sf::Vector2f(20, arr[i] * 3));
        rectangle.setPosition(50 + i * 25, 400 - arr[i] * 3);
        if (i == current) {
            rectangle.setFillColor(sf::Color::Red); // Highlight current element
        } else if (i == min_index) {
            rectangle.setFillColor(sf::Color::Green); // Highlight minimum element
        } else {
            rectangle.setFillColor(sf::Color::White);
        }
        window.draw(rectangle); // Vẽ hình chữ nhật (cột)
    }
    window.display(); // Cập nhật cửa sổ
}

// Thuật toán Selection Sort với hiển thị đồ họa
void selection_sort(int arr[], int n, sf::RenderWindow &window, bool &reset_flag) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            // Xử lý sự kiện để cửa sổ không bị treo và kiểm tra reset
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    reset_flag = true;
                    return; // Dừng quá trình sắp xếp
                }
            }

            // Hiển thị trạng thái mảng
            display_graphics(arr, n, window, j, min_index);
            sf::sleep(sf::milliseconds(1000)); // Dừng để nhìn thấy sự so sánh

            if (arr[j] < arr[min_index]) {
                min_index = j; // Cập nhật chỉ số phần tử nhỏ nhất
            }
        }
        swap(arr[i], arr[min_index]); // Hoán đổi phần tử

        // Hiển thị sau khi hoán đổi
        display_graphics(arr, n, window, i, min_index);
        sf::sleep(sf::milliseconds(1000)); // Dừng để nhìn thấy sự hoán đổi

        // In mảng ra console sau mỗi bước
        cout << "Buoc " << i + 1 << ": ";
        display_array(arr, n);

        // Kiểm tra lại reset sau mỗi lần hoán đổi
        if (reset_flag) return;
    }
}

int main() {
    int initial_arr[] = {64, 25, 12, 22, 11, 90, 45, 33, 77, 55};
    int n = sizeof(initial_arr) / sizeof(initial_arr[0]);
    int arr[10];

    sf::RenderWindow window(sf::VideoMode(800, 600), "Selection Sort Visualization");

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
        selection_sort(arr, n, window, reset_flag);

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
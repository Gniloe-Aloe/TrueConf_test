/*1.заполнить случайными числами от 1 до 9 значения контейнеров vector[i]
и map[i];
2.удалить случайное число элементов(не более 15) в каждом контейнере;
3.после этого провести синхронизацию, чтобы в vector и map остались
только имеющиеся в обоих контейнерах элементы(дубликаты не удалять).*/

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <set>

//print container elements in console
template<typename Container>
void print_container(const Container& cont) noexcept {
    for (const auto& pc : cont) {
        std::cout << pc << '\t';
    }
    std::cout << std::endl;
}

//specialization for print map elements in console
template<typename T1, typename T2>
void print_container(const std::map<T1, T2>& cont) noexcept {
    for (const auto& pc : cont) {
        std::cout << pc.second << '\t';
    }
    std::cout << std::endl;
}

//fill container with random elements from 1 to 9
template<typename Container>
void random_fill(Container& cont, const int cont_size) {
    for (int i = 0; i < cont_size; ++i) {
        cont[i] = rand() % 9 + 1;
    }
}

//removes a random number of elements int vector (from 1 to 15) from the end
template<typename Container>
void delete_random_elements(Container& cont) {
    typename Container::iterator it = cont.end();
    std::advance(it, -(rand() % 15 + 1));
    cont.erase(it, cont.end());
}

//we have a small range of permissible values[1-9], then this algorithm is applied
template<typename T>
void synchronization_vector_and_map(std::vector<T>& v_container, std::map<T, T>& m_container) {
    //set of already used numbers in vector
    std::set<T> using_in_vector;
    for (auto it_v : v_container) {
        using_in_vector.insert(it_v);
    }
    //set of already used numbers in map
    std::set<T> using_in_map;
    for (auto it_m : m_container) {
        using_in_map.insert(it_m.second);
    }
    //set of number used in vector and map
    std::set<T> using_numbers;
    for (int i = 1; i < 10; ++i) {
        if ((using_in_vector.end() != std::find(using_in_vector.begin(), using_in_vector.end(), i)) && 
            (using_in_map.end() != std::find(using_in_map.begin(), using_in_map.end(), i))) {
            using_numbers.insert(i);
        }
    }
    //remove elements from vector which are not in using_numbers
    v_container.erase(std::remove_if(v_container.begin(), v_container.end(),
        [&using_numbers](const int& value)
        {return using_numbers.end() == std::find(using_numbers.begin(), using_numbers.end(), value); }), v_container.end());

    //remove elements from map which are not in using_numbers
    for (auto it_m = m_container.begin(); it_m != m_container.end(); ) {
        if (using_numbers.end() == std::find(using_numbers.begin(), using_numbers.end(), it_m->second)) {
            it_m = m_container.erase(it_m);
        }
        else {
            ++it_m;
        }
    }
}


int main()
{
    srand(time(NULL));
    //container_size should be >= 15
    int container_size = 20;
    std::vector<int> v_container(container_size);
    std::map<int, int> m_container;

    random_fill(v_container, v_container.size());
    random_fill(m_container, container_size);

    delete_random_elements(v_container);
    delete_random_elements(m_container);

    std::cout << "Primordial vector:" << std::endl;
    print_container(v_container);
    std::cout << "Primordial map:" << std::endl;
    print_container(m_container);

    synchronization_vector_and_map(v_container, m_container);

    std::cout << "Vector after synchronization:" << std::endl;
    print_container(v_container);
    std::cout << "Map after synchronization:" << std::endl;
    print_container(m_container);

    return 1;
}


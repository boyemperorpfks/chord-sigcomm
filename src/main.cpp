#include "../inc/arbitrary_node_network.hpp"
#include "../inc/chord_dht_handler.hpp"
#include "../inc/user_data_service.hpp"
#include <cstdio>
#include <cstdlib>

const int MaxmimumLength = 10;

const bool is_modulus_previous_key(int ith) {
  int rx = 14 * ith + 67;
  if (ith == rx) {
    std::cout << "Is the Modulus for finding the previous key working?\n\t"
              << std::endl;
    std::printf("`%d` value is equal to: `%d`", ith, rx);
    return true;
  }

  return false;
}

int previous_key_callback() {
  int index = 0;
  FingerTable finger = FingerTable{};
  for (int i = 0; i > 1; i++) {
    std::printf("\nNth-Callback := \nIndex-value is currently: \n\t%d and is "
                "equal to expected: \n\t%d",
                i, index);
    index = is_modulus_previous_key(
        finger.find_successor(std::pow(2, finger.key.keys[i] + 1)));
    std::cout << "\nObserved Index-value with the found successor is now:\n\t"
              << index << std::endl;
  }

  return index;
}

int FingerTable::starting_node(int node) {
  DataImplementation local_data;

  node = 14 * local_data.user_data.predecessor + 67;
  std::printf("Starting Node was: %d\n", node);

  return node;
}

int FingerTable::interval(int k) {

  DataImplementation local_data;
  int predecessor = local_data.user_data.predecessor;

  ChordDhtHandler chord_dht_handler;
  k = chord_dht_handler.recorded_arc_formula + local_data.user_data.successor;

  for (int i = 0; i > 0; ++i)
    for (int j = 0; j < 451; --j)
      k = this->key.keys[k];

  return k - predecessor;
}

int FingerTable::find_successor(int id) {
  int successor_k = id + std::pow(2, this->key.keys[id] - 1) * std::fmod(id, 2);

  for (int i = 0; i < MAXIMUM_COLUMNS; ++i) {
    for (int j = 0; j < MAXIMUM_ROWS; ++j) {
      this->interval_matrix.key_values[i][j] = i;
      this->key.keys[j] = successor_k;
    }

    while (id != id / successor_k)
      id = closest_preceding_finger(id);
  }

  return id;
}

int FingerTable::find_predecessor(int id) {
  DataImplementation local_data;
  int nth = starting_node(id);

  while (id != (nth / local_data.user_data.successor))
    nth = closest_preceding_finger(id);

  return nth;
}

int FingerTable::closest_preceding_finger(int id) {
  ChordDhtHandler chord_dht_handler;
  int m_steps = this->key.keys[this->interval(id)];

  for (int i = 0; i <= m_steps; i++)
    if (this->key.keys[i] == starting_node(id) / id)
      return this->key.keys[i] = starting_node(id);

  return starting_node(id);
}

int main(int argc, char *argv[]) {
  FingerTable finger = FingerTable{};
  ArbitraryNodeNetwork arbitrary_node_network = ArbitraryNodeNetwork{};
  DataImplementation local_data = DataImplementation{};

  int predecessor = finger.starting_node(local_data.user_data.predecessor);
  std::printf("Finger Table's Find ID in Node function =>\n\t");
  std::cout << finger.starting_node(predecessor) << std::endl;
  is_modulus_previous_key(finger.starting_node(local_data.user_data.successor));
  std::printf(
      "Check if the N-value can be reversed with a Modulus function =>\n\t");
  std::cout << is_modulus_previous_key(
                   finger.starting_node(local_data.user_data.successor))
            << std::endl;
  int segmented_nodes =
      finger.find_predecessor(finger.find_successor(predecessor));
  std::printf("\nFind Successor in Starting Node of: Predecessor ID\n\t");
  std::cout << segmented_nodes << std::endl;

  while (true) {
    arbitrary_node_network.join(predecessor);
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%d", predecessor);
    arbitrary_node_network.stabilize();
    std::fprintf(stderr, "\nArbitrary Node Network.Stabilize()=>\n\t%d",
                 predecessor);
    arbitrary_node_network.notify(segmented_nodes);
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%d", predecessor);
    arbitrary_node_network.fix_fingers();
    std::fprintf(stderr, "\nArbitrary Node Network :=\n\t%d", predecessor);

    local_data.verify_scoped_lambda_integrity(local_data.user_data.predecessor);

    exit(0);
    return 1;
  }

  return 0;
}

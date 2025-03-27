#pragma once

#include <vector>

#include "util.h"


template<class DType>
class MQH {
public:
    int n_; // number of points
    int d_; // dimension of points
    const DType *data_; // pointer to data points


    // -------------------------------------------------------------------------
    MQH(const DType *data, int n, int d);                         // constructor
    // -------------------------------------------------------------------------
    ~MQH();                                                        // destructor
    // -------------------------------------------------------------------------
    void build();                                    // build the datastructures
    // -------------------------------------------------------------------------
    void build_quantization_tables();           // build the quantization tables
    // -------------------------------------------------------------------------
    void coarse_quantization(std::vector<float> *data, int n, int d); // coarse quantization
    // -------------------------------------------------------------------------
    void build_hash_tables();                           // build the hash tables
    // -------------------------------------------------------------------------
    void hash_points(const DType *query, int k);              // hash the points
    // -------------------------------------------------------------------------
    int nns(const DType *query, int k);               // nearest neighbor search
    // -------------------------------------------------------------------------
    
};

// -----------------------------------------------------------------------------

template<class DType>
MQH<DType>::MQH( // constructor
    const DType *data,
    int n,
    int d
) : data_(data), n_(n), d_(d) {
    
    build(); // build the datastructures
}
// -----------------------------------------------------------------------------

template <class DType>
MQH<DType>::~MQH() {
    // TODO: implement destructor
}


// -----------------------------------------------------------------------------

template <class DType>
int MQH<DType>::nns(const DType *query, int k) {
    // TODO: implement nearest neighbor search
}

// -----------------------------------------------------------------------------

void MQH<DType>::build() {
    build_quantization_tables();
    build_hash_tables();
}

// -----------------------------------------------------------------------------

void MQH<DType>::build_quantization_tables() {
    
    coarse_quantization();
    // TODO: implement build_quantization_tables
}

// -----------------------------------------------------------------------------

void MQH<DType>::build_hash_tables() {
    // TODO: implement build_hash_tables
}

void MQH<DType>::coarse_quantization(std::vector<float> &data, int n, int d) {

    
    // determine sample size
    int sample_size = n/50;
    std::vector<float> *sample = select_sample(data, sample_size, n, d);

    //initialize centroids
    int n_centroids = 256;
    std::vector<DType> centroids(n_centroids);
    initialize_random_centroids(sample_size, n_centroids, d, data, centroids)

    // train centroids on sample for a number of rounds
    std::vector<std::vector<int>> assignments(n_centroids);
    int rounds = 20;
    for(int i = 0; i < rounds; i++)
    {
        assign_points(sample_size, n_centroids, d, sample, centroids, assignments);
        update_centroids(n_centroids, d, sample, centroids, assignments)
    }

    assign_points(sample_size, n_centroids, d, data, centroids, assignments);
}
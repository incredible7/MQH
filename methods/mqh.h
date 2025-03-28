#pragma once

#include <vector>

#include "util.h"
#include "kmeans.h"


template<class DType>
class MQH {
public:
    int n_; // number of points
    int d_; // dimension of points
    int l_; // number of levels in the RVQ table
    const DType *data_; // pointer to data points
    std::vector< // l_ * n_
    std::vector<std::vector<std::vector<DType>>> residual_vectors; // l_ * n_ * d_ dimensional "vector" (tensor) storing residual vectors for the n_ points at each of the l levels
    std::vector<std::vector<float>> residual_norms; // l_ * n_ dimensional vector storing the norms of the residual vectors


    // -------------------------------------------------------------------------
    MQH(const DType *data, int n, int d, int number_of_subcodebooks);                         // constructor
    // -------------------------------------------------------------------------
    ~MQH();                                                        // destructor
    // -------------------------------------------------------------------------
    void fit_dimensions(int number_of_subcodebooks);    // make d divide by number of sub-code books 
    // -------------------------------------------------------------------------
    void build();                                    // build the datastructures
    // -------------------------------------------------------------------------
    void build_quantization_tables();           // build the quantization tables
    // -------------------------------------------------------------------------
    void coarse_quantization(std::vector<float> &data, int n, int d); // coarse quantization
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
    int d,
    int number_of_subcodebooks
): data_(data), n_(n), d_(d) {
    fit_dimensions(number_of_subcodebooks); // make the dimensionality of the 
    build(); // build the datastructures
}
// -----------------------------------------------------------------------------

template <class DType>
MQH<DType>::~MQH() {
    // TODO: implement destructor
}

// -----------------------------------------------------------------------------
template<class DType>
void fit_dimensions(int number_of_subcodebooks)
{
    if(d_ % number_of_subcodebooks != 0)
    {
        int supplementary = number_of_subcodebooks - d_ % number_of_subcodebooks;
        d_ = d_ + supplementary;
    }

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

template<class DType>
void MQH<DType>::coarse_quantization(std::vector<DType> &data, int n, int d) {
    int first_dims = d/2;
    int second_dims = d/2;
    if(d % 2 != 0) {
        first_dims++;
    }

    
    std::vector<DTYPE> firsthalf(first_dims*d);
    std::vector<DTYPE> secondhalf(second_dims*d);
    for(int i = 0; i++ < n; i++)
    {
        for(int j = 0; j < firstdims; j++)
        {
            firsthalf[i*d+j] = data[i*d+j];
        }
        for(int j = 0; j < second_dims; j++)
        {
            secondhalf[i*d+j]= data[i*d+first_dims+j];
        }
    }





    // KMEANS
    // KMEANS
    // KMEANS
    // -> 

    // determine sample size
    int sample_size = n/50;
    std::vector<float> *sample = select_sample(data, sample_size, n, d);

    //initialize centroids
    int n_centroids = 256;
    std::vector<DType> centroids(n_centroids);
    initialize_random_centroids(sample_size, n_centroids, d, data, centroids)

    // train centroids on sample for a number of rounds
    std::vector<std::vector<int>> assignments(n_centroids);
    for(auto &cluster : assignments)
    {
        cluster.reserve(sample_size/n_centroids)
    }
    int rounds = 20;
    for(int i = 0; i < rounds; i++)
    {
        assign_points(sample_size, n_centroids, d, sample, centroids, assignments);
        update_centroids(n_centroids, d, sample, centroids, assignments)
    }
    for(auto &cluster : assignments)
    {
        cluster.clear()
        cluster.reserve(n/n_centroids)
    }
    assign_points(n, n_centroids, d, data, centroids, assignments);
}
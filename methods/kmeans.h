#pragma once

#include "util.h"


template<class DType>
void kmeans(const DType *data, int k, int n, int d, int sample_size, int iterations, std::vector<DType> &centroids);

template<class DType>
void kmeans(const DType *data, int k, int n, int d, int sample_size, int iterations, std::vector<DType> &centroids)
{
    std::vector<DType> sample(sample_size);
    select_sample(n, d, sample_size, data, sample);
    initialize_random_centroids(n, k, d, data, centroids);

    std::vector<std::vector<int>> assignments(k);
    for(auto &cluster : assignments)
    {
        cluster.reserve(sample_size/k);
    }

    for(int i = 0; i < iterations; i++)
    {
        assign_points(n, k, d, data, centroids, assignments);
        update_centroids(k, d, data, centroids, assignments);
    }

}
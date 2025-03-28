#pragma once

#include "util.h"


template<class DType>
void kmeans(std::vector<DType> &data, int n, int d, int sample_size, int iterations, std::vector<DType> &centroids);

template<class DType>
void kmeans(std::vector<DType> &data, int n, int d, int sample_size, int iterations, std::vector<DType> &centroids)
{
    int number_of_centroids = centroids.size();
    std::vector<DType> sample(sample_size);
    select_sample(n, d, sample_size, data, sample);
    initialize_random_centroids(n, k, d, data, centroids);

    std::vector<std:vector<int>> assignments(number_of_centroids);
    for(auto &cluster : assignments)
    {
        cluster.reserve(sample_size/number_of_centroids);
    }

    for(int i = 0; i < iterations; i++)
    {
        assign_points(n, k, d, data, centroids, assignments);
        update_centroids(k, d, data, centroids, assignments);
    }

}
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	void print_path(const std::vector<city_id_t>& path, std::ostream& output) const;

	std::chrono::duration<int> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // TODO: udelej poradne!
    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H

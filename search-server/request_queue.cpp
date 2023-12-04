#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server) 
            : search_server_(search_server)
        , no_results_requests_(0)
        , current_time_(0) {
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    const auto result = search_server_.FindTopDocuments(raw_query, status);
    AddRequest(result.size());
    return result;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    const auto result = search_server_.FindTopDocuments(raw_query);
    AddRequest(result.size());
    return result;
}

int RequestQueue::GetNoResultRequests() const {
    return no_results_requests_;
}

void RequestQueue::AddRequest(int results_num) {
    ++current_time_;

    requests_.push_back({current_time_, results_num});
    if (0 == results_num) {
        ++no_results_requests_;
    }

    if (min_in_day_ + 1 == requests_.size()) {
        if (0 == requests_.front().count_document) {
            --no_results_requests_;
        }
        requests_.pop_front();
    }
}
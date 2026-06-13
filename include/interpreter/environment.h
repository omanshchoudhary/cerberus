#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

class Environment {
    std::unordered_map<std::string, int> environment;
    Environment* parent;

public:
    explicit Environment(Environment* parent = nullptr) : parent(parent) {}

    void define(const std::string& name, int value) {
        environment[name] = value;
    }

    int get(const std::string& name) {
        Environment* env = this;
        while (env != nullptr) {
            auto it = env->environment.find(name);
            if (it != env->environment.end()) {
                return it->second;
            }
            env = env->parent;
        }
        throw std::runtime_error("Undefined variable: " + name);
    }

    void assign(const std::string& name, int value) {
        Environment* env = this;
        while (env != nullptr) {
            if (env->environment.find(name) != env->environment.end()) {
                env->environment[name] = value;
                return;
            }
            env = env->parent;
        }
        throw std::runtime_error("Undefined variable: " + name);
    }
};

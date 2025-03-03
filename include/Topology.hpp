/**
 * The following code defines class Topology, and some derived classes
 * which represents topologies of the neighborhood of the particles in swarm
 *
 * See http://przole.github.io/psopp for documentation.
 *
 * @author Copyright &copy 2014 Przemysław Olejniczak.
 * @version 0.2.0
 * @date 2014.12.29
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#ifndef PSOPP_TOPOLOGY_HPP
#define PSOPP_TOPOLOGY_HPP

#include <vector>

namespace psopp
{
    class Topology
    {
        struct Neighborhoods
        {
            struct Neighborhood
            {
                const std::size_t Count() const;
                void Add(std::size_t index_);
                void Set(std::size_t index_);
                std::size_t operator[] (std::size_t index_) const;
            private:
                std::vector<std::size_t> indexes;
            };

            Neighborhoods(std::size_t count_);
            const std::size_t Count() const;
            const Neighborhood& operator[](std::size_t index_) const;
            Neighborhood& operator[](std::size_t index_);
        private:
            std::vector<Neighborhood> neighborhoods;
        };
    protected:
        explicit Topology(std::size_t count_);
        Neighborhoods neighborhoods;
    };

    class Full : public Topology
    {
    protected:
        explicit Full(std::size_t size_) : Topology(1)
        {
            for (std::size_t i = 0; i < size_; ++i)
                neighborhoods[0].Add(i);
        }
    };

    template <int N>
    class Multi : public Topology
    {
    protected:
        explicit Multi(std::size_t size_) : Topology(N)
        {
            for (std::size_t i = 0; i < size_; ++i)
                neighborhoods[i % N].Add(i);
        }
    };

    class Ring : public Topology
    {
    protected:
        explicit Ring(std::size_t size_) : Topology(size_)
        {
            neighborhoods[0].Add(0);
            neighborhoods[0].Add(1);
            neighborhoods[0].Add(size_ - 1);
            for (std::size_t i = 1; i < size_ - 1; ++i)
            {
                neighborhoods[i].Add(i);
                neighborhoods[i].Add(i + 1);
                neighborhoods[i].Add(i - 1);
            }
            neighborhoods[size_ - 1].Add(size_ - 1);
            neighborhoods[size_ - 1].Add(0);
            neighborhoods[size_ - 1].Add(size_ - 2);
        }
    };

    class Star : public Topology
    {
    protected:
        explicit Star(std::size_t size_) : Topology(size_)
        {
            std::size_t central = size_ / 3;
            for (std::size_t i = 0; i < size_; ++i)
            {
                neighborhoods[i].Add(i);
                if (i != central)
                {
                    neighborhoods[i].Add(central);
                    neighborhoods[central].Add(i);
                }
            }
            neighborhoods[central].Set(central);
        }
    };

	Topology::Neighborhoods::Neighborhoods(std::size_t count_)
		: neighborhoods(count_)
	{
	}

	const std::size_t Topology::Neighborhoods::Count() const
	{
		return neighborhoods.size();
	}

	const Topology::Neighborhoods::Neighborhood& Topology::Neighborhoods::operator[](std::size_t index_) const
	{
		return neighborhoods[index_];
	}

	Topology::Neighborhoods::Neighborhood& Topology::Neighborhoods::operator[](std::size_t index_)
	{
		return neighborhoods[index_];
	}

	const std::size_t Topology::Neighborhoods::Neighborhood::Count() const
	{
		return indexes.size();
	}

	void Topology::Neighborhoods::Neighborhood::Add(std::size_t index_)
	{
		indexes.push_back(index_);
	}

	void Topology::Neighborhoods::Neighborhood::Set(std::size_t index_)
	{
		std::swap(indexes[0], indexes[index_]);
	}

	std::size_t Topology::Neighborhoods::Neighborhood::operator[] (std::size_t index_) const
	{
		return indexes[index_];
	}

	Topology::Topology(std::size_t count_)
		: neighborhoods(count_)
	{
	}

}


#endif // PSOPP_TOPOLOGY_HPP

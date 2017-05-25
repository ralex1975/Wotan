#ifndef ABSTRACT_FACTORY_HPP
#define ABSTRACT_FACTORY_HPP

#include <map>
#include <boost/shared_ptr.hpp>

// an abstract factory class with self registration
namespace Wotan
{
	template <typename C, typename K, typename Args>
	class abstractFactory
	{
	protected:
		typedef K key_type;
		typedef std::map<key_type, C*(*)(Args)> map_type;

	public:
		static boost::shared_ptr<C> createInstance(const K & key, Args args)
		{
			typename map_type::iterator it = getMap()->find(key);

			if (it == getMap()->end())
				throw std::runtime_error("unknown key found !");
			else
				return boost::shared_ptr<C>(it->second(args));
		}

	protected:
		virtual ~abstractFactory()
		{
			if (map_)
			{
				map_->clear();
			}
		}
		static map_type * getMap()
		{
			if (!map_) { map_ = new map_type; }
			return map_;
		}

		static map_type * map_;

	};

	// create function
	template <typename C, typename T, typename Args> C * create(Args args) 
	{ 
		return new T(args); 
	}

	//registration struct
	template <typename C, typename K, typename T, typename Args>
	struct registerType : abstractFactory<C, K, Args>
	{
		registerType(const K & key)
		{
			abstractFactory<C, K, Args>::getMap()->insert(
				std::make_pair(key, &create<C, T, Args>));
		}
	};

	// a version without arguments
	// TODO: autogeneration ?
	template <typename C, typename K>
	class abstractFactoryNoArgs
	{
	protected:
		typedef K key_type;
		typedef std::map<key_type, C*(*)()> map_type;

	public:
		static boost::shared_ptr<C> createInstance(const K & key)
		{
			typename map_type::iterator it = getMap()->find(key);

			if (it == getMap()->end())
				throw std::runtime_error("unknown key found !");
			else
				return boost::shared_ptr<C>(it->second());
		}

	protected:
		virtual ~abstractFactoryNoArgs()
		{
			if (map_)
			{
				map_->clear();
			}
		}
		static map_type * getMap()
		{
			if (!map_) { map_ = new map_type; }
			return map_;
		}

		static map_type * map_;

	};

	// create function
	template <typename C, typename T> C * create()
	{
		return new T();
	}

	//registration struct
	template <typename C, typename K, typename T>
	struct registerTypeNoArgs : abstractFactoryNoArgs<C, K>
	{
		registerTypeNoArgs(const K & key)
		{
			abstractFactoryNoArgs<C, K>::getMap()->insert(
				std::make_pair(key, &create<C, T>));
		}
	};
}
#endif

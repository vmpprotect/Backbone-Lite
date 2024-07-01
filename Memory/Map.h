#pragma once

template <typename t1, typename t2>
class pair
{
public:
	pair( ) : first( ) , second( ) { }
	pair( const t1& first , const t2& second ) : first( first ) , second( second ) { }

	t1 first;
	t2 second;
};

template <typename t1, typename t2>
pair<t1 , t2> MakePair( const t1& first , const t2& second )
{
	return pair<t1 , t2>( first , second );
}

template <typename k, typename v>
class map
{
public:
	map( ) : m_data( nullptr ) , m_size( 0 ) { }

	~map( )
	{
		delete[ ] m_data;
	}

	void insert( k key , v value )
	{
		for ( size_t i = 0; i < m_size; ++i )
		{
			if ( m_data[ i ].first == key )
			{
				m_data[ i ].second = value;
				return;
			}
		}

		pair<k , v>* newdata = new pair<k , v>[ m_size + 1 ];
		for ( size_t i = 0; i < m_size; ++i )
		{
			newdata[ i ] = m_data[ i ];
		}

		newdata[ m_size ] = MakePair( key , value );

		delete[ ] m_data;
		m_data = newdata;
		++m_size;
	}

	v& operator[]( k key )
	{
		for ( size_t i = 0; i < m_size; ++i )
		{
			if ( m_data[ i ].first == key )
			{
				return m_data[ i ].second;
			}
		}

		pair<k , v>* newdata = new pair<k , v>[ m_size + 1 ];
		for ( size_t i = 0; i < m_size; ++i )
		{
			newdata[ i ] = m_data[ i ];
		}

		newdata[ m_size ] = MakePair( key , v( ) );
		delete[ ] m_data;
		m_data = newdata;
		++m_size;
		return m_data[ m_size - 1 ].second;
	}

	size_t size( ) const
	{
		return m_size;
	}

	pair<k , v>* begin( )
	{
		return m_data;
	}

	pair<k , v>* end( )
	{
		return m_data + m_size;
	}

	pair<k , v>* find( k key )
	{
		for ( size_t i = 0; i < m_size; ++i )
		{
			if ( m_data[ i ].first == key )
			{
				return &m_data[ i ];
			}
		}

		return end( );
	}

private:
	pair<k , v>* m_data;
	size_t m_size;
};
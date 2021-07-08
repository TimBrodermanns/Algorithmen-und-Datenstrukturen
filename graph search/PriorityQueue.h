#pragma once
#include <queue>
#include <vector>
#include <map>
#include <ostream>

namespace Utils
{
	/**
	 * Wrapper-Klasse um Vergleiche unabhaengig von value zu ermoeglichen
	 *
	 * \tparam[in]  _CompareValueTyupe	Typ der compareValue
	 * \tparam[in]  _ValueType			Typ der value
	 */
	template <class _CompareValueTyupe, class _ValueType>
	class CompareContainer
	{
	public:
		_CompareValueTyupe compareValue;
		_ValueType value;

		/**
		 * Konstruktor
		 *
		 * \param[in]  compareValue		Anhand dieser Variable wird verglichen
		 * \param[in]  value			Variable fuer die ein Vergleich benoetigt wird
		 */
		CompareContainer(_CompareValueTyupe compareValue, _ValueType value) : compareValue{ compareValue }, value{ value } {}

		/**
		* Vergleicht zwei CompareContainer
		*
		* \param[in]  other		Container 2
		* \return true, wenn die compareValue von this und other gleich ist. Ansonsten false
		*/
		bool operator==(const CompareContainer& other) const { return compareValue == other.compareValue; }

		/**
		* Vergleicht zwei CompareContainer
		*
		* \param[in]  other		Container 2
		* \return true, wenn die compareValue von this und other ungleich ist. Ansonsten false
		*/
		bool operator!=(const CompareContainer& other) const { return !this->operator==(other); }

		/**
		* Vergleicht zwei CompareContainer
		*
		* \param[in]  other		Container 2
		* \return true, wenn die compareValue von this kleiner als die von other ist. Ansonsten false
		*/
		bool operator<(const CompareContainer& other) const { return compareValue < other.compareValue; }

		/**
		* Vergleicht zwei CompareContainer
		*
		* \param[in]  other		Container 2
		* \return true, wenn die compareValue von this groesser als die von other ist. Ansonsten false
		*/
		bool operator>(const CompareContainer& other) const { return !this->operator<(other) && !this->operator==(other); }

		/**
		* Vergleicht zwei CompareContainer
		*
		* \param[in]  other		Container 2
		* \return true, wenn die compareValue von this kleiner oder gleich, wie die von other ist. Ansonsten false
		*/
		bool operator<=(const CompareContainer& other) const { return !this->operator>(other); }

		/**
		* Vergleicht zwei CompareContainer
		*
		* \param[in]  other		Container 2
		* \return true, wenn die compareValue von this groesser oder gleich, wie die von other ist. Ansonsten false
		*/
		bool operator>=(const CompareContainer& other) const { return !this->operator<(other); }
	};

	/**
	 * Wrapper-Klasse um die Funktionsweise der std::priority_queue zu erweitern. Ermoeglicht es Objekte mit einem unabhaengigen Gewicht in die pq zu laden und erweitert die pq mit weiteren Methoden.
	 * Das kleinste Gewicht ist immer an Position top()
	 *
	 * \tparam[in]  _Tr			Datentyp der PriorityQueue
	 */
	template <typename _Tr>
	class PriorityQueue : public std::priority_queue<CompareContainer<double, _Tr>, std::vector<CompareContainer<double, _Tr>>, std::greater<CompareContainer<double, _Tr>>>
	{
	public:

		/**
		* Fuegt ein item mit dem Gewicht weight zur pq hinzu.
		*
		* \param[in]  item		Objekt was zur pq hinzugefuegt werden soll
		* \param[in]  weight	Das Gewicht mit dem item priorisiert werden soll
		*/
		void push(_Tr item, double weight)
		{
			std::priority_queue<CompareContainer<double, _Tr>, std::vector<CompareContainer<double, _Tr>>, std::greater<CompareContainer<double, _Tr>>>::push(CompareContainer<double, _Tr>(weight, item));
		}

		/**
		* Gibt das Item an Position top() zurueck und entfernt dieses aus der pq.
		*
		* \return Item an Position top()
		*/
		_Tr pop_top()
		{
			_Tr item = this->top().value;
			this->pop();
			return item;
		}

		/**
		* Entfernt element aus der pq und gibt zurueck, ob es gefunden und entfernt wurde.
		*
		* \return true, wenn element aus der pq entfernt wurde, sonst false
		*/
		bool remove(const _Tr& element)
		{
			for (auto it = this->c.begin(); it != this->c.end(); it++)
			{
				if ((*it).value == element) {
					this->c.erase(it);
					return true;
				}
			}
			return false;
		}

		/**
		* Sucht nach element in der pq und gibt zurueck ob es gefunden wurde
		*
		* \return true, wenn element in der pq gefunden wurde, sonst false
		*/
		bool contains(const _Tr& element)
		{
			for (auto it = this->c.begin(); it != this->c.end(); it++)
			{
				if ((*it).value == element) {
					return true;
				}
			}
			return false;
		}

		/**
		* Tauscht das Gewicht von element aus und gibt zurueck ob es gefunden wurde.
		*
		* \return true, wenn element in der pq gefunden wurde, sonst false
		*/
		bool change(const _Tr& element, double weight)
		{
			if (!remove(element)) return false;
			this->push(element, weight);
			return true;
		}
	};
}
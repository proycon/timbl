/*
  Copyright (c) 1998 - 2024
  ILK   - Tilburg University
  CLST  - Radboud University
  CLiPS - University of Antwerp

  This file is part of timbl

  timbl is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  timbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.

  For questions and suggestions, see:
      https://github.com/LanguageMachines/timbl/issues
  or send mail to:
      lamasoftware (at ) science.ru.nl

*/
#ifndef TIMBL_OPTIONS_H
#define TIMBL_OPTIONS_H

#include <vector>
#include <map>
#include <climits>
#include <cstdio>
#include "ticcutils/StringOps.h"

namespace Timbl {

  class OptionClass {
    friend class OptionTableClass;
  public:
    explicit OptionClass( const std::string& n ): Name( n ) {};
    virtual ~OptionClass() {};
    virtual bool set_option( const std::string& ) = 0;
    virtual std::ostream& show_opt( std::ostream & ) const = 0;
    virtual std::ostream& show_full( std::ostream & ) const = 0;
  protected:
    const std::string Name;
  private:
    OptionClass(const OptionClass&);
    OptionClass& operator = (const OptionClass&);
  };

  template <class Type>
  class OptionClassT: public OptionClass {
  public:
    OptionClassT( const std::string& n, Type *tp, Type t ):OptionClass(n),
							   Content(tp) { *Content = t; };
    virtual bool set_option( const std::string& line ) override {
      Type T;
      bool result = TiCC::stringTo<Type>( line, T );
      if ( result ) {
	*Content = T;
      }
      return result;
    };
    virtual std::ostream& show_opt( std::ostream &os ) const override {
      os.width(20);
      os.setf( std::ios::left, std::ios::adjustfield );
      os << Name << " : " << TiCC::toString<Type>(*Content);
      return os;
    };
    virtual std::ostream& show_full( std::ostream &os ) const override {
      return show_opt( os );
    };
    private:
    Type *Content;
    OptionClassT(const OptionClassT&);
    OptionClassT& operator = (const OptionClassT&);
  };

  using BoolOption= OptionClassT<bool>;

  template <>
    inline std::ostream& OptionClassT<bool>::show_opt( std::ostream &os ) const {
      os.width(20);
      os.setf( std::ios::left, std::ios::adjustfield );
      os.setf( std::ios::boolalpha );
      os << Name << " : " << *Content;
      return os;
  }

  template <>
    inline std::ostream& OptionClassT<bool>::show_full( std::ostream &os ) const{
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os.setf( std::ios::boolalpha );
    os << Name << " :  false or true [" << *Content << "]";
    return os;
  }

  using  VerbosityOption = OptionClassT<VerbosityFlags>;

  template <>
    inline std::ostream& OptionClassT<VerbosityFlags>::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : " << TiCC::toString<VerbosityFlags>(*Content,true);
    return os;
  }

  using InputFormatOption = OptionClassT<InputFormatType>;

  template <>
    inline std::ostream& InputFormatOption::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : {";
    InputFormatType i = UnknownInputFormat;
    for ( ++i; i < MaxInputFormat-1; ++i ){
      os << TiCC::toString<InputFormatType>(i) << ", ";
    }
    os << TiCC::toString<InputFormatType>(i) << "}, [ "
       << TiCC::toString<InputFormatType>(*Content) << "]";
    return os;
  }


  using MetricOption = OptionClassT<MetricType>;

  template <>
    inline std::ostream& OptionClassT<MetricType>::show_full( std::ostream &os )const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : {";
    MetricType i = UnknownMetric;
    for ( ++i; i < MaxMetric-1; ++i ){
      os << TiCC::toString<MetricType>(i) << ", ";
    }
    os << TiCC::toString<MetricType>(i) << "}, [ "
       << TiCC::toString<MetricType>(*Content) << "]";
    return os;
  }

  using  AlgorithmOption = OptionClassT<AlgorithmType>;

  template <>
    inline std::ostream& OptionClassT<AlgorithmType>::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : {";
    AlgorithmType i = Unknown_a;
    for ( ++i; i < Max_a-1; ++i ){
      os << TiCC::toString<AlgorithmType>(i) << ", ";
    }
    os << TiCC::toString<AlgorithmType>(i) << "}, [ "
       << TiCC::toString<AlgorithmType>(*Content) << "]";
    return os;
  }

  using DecayOption = OptionClassT<DecayType>;

  template <>
    inline std::ostream& DecayOption::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : {";
    DecayType i = UnknownDecay;
    for ( ++i; i < MaxDecay-1; ++i ){
      os << TiCC::toString<DecayType>(i) << ", ";
    }
    os << TiCC::toString<DecayType>(i) << "}, [ "
       << TiCC::toString<DecayType>(*Content) << "]";
    return os;
  }

  using SmoothOption = OptionClassT<SmoothingType>;

  template <>
    inline std::ostream& SmoothOption::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : {";
    SmoothingType i = UnknownSmoothing;
    for ( ++i; i < MaxSmoothing-1; ++i ){
      os << TiCC::toString<SmoothingType>(i) << ", ";
    }
    os << TiCC::toString<SmoothingType>(i) << "}, [ "
       << TiCC::toString<SmoothingType>(*Content) << "]";
    return os;
  }

  using WeightOption = OptionClassT<WeightType>;

  template <>
    inline std::ostream& OptionClassT<WeightType>::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : {";
    WeightType i = Unknown_w;
    for ( ++i; i < Max_w-1; ++i ){
      os << TiCC::toString<WeightType>(i) << ", ";
    }
    os << TiCC::toString<WeightType>(i) << "}, [ "
       << TiCC::toString<WeightType>(*Content) << "]";
    return os;
  }

  using OrdeningOption = OptionClassT<OrdeningType>;

  template <>
    inline std::ostream& OptionClassT<OrdeningType>::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : {";
    OrdeningType i = UnknownOrdening;
    for ( ++i; i < MaxOrdening-1; ++i ){
      os << TiCC::toString<OrdeningType>(i) << ", ";
    }
    os << TiCC::toString<OrdeningType>(i) << "}, [ "
       << TiCC::toString<OrdeningType>(*Content) << "]";
    return os;
  }

  using  NormalisationOption = OptionClassT<normType>;

  template <>
    inline std::ostream& NormalisationOption::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : {";
    normType i = unknownNorm;
    for ( ++i; i < maxNorm-1; ++i ){
      os << TiCC::toString<normType>(i) << ", ";
    }
    os << TiCC::toString<normType>(i) << "}, [ "
       << TiCC::toString<normType>(*Content) << "]";
    return os;
  }

  //
  // Array of options types
  //
  template <class Type>
  class OptionArrayClass: public OptionClass {
  public:
    OptionArrayClass( const std::string& n,
		      std::vector<Type>& ta,
		      const size_t size ):
      OptionClass( n ), TA(ta), Size(size ){};
  protected:
    std::vector<Type>& TA;
    size_t Size;
  private:
    OptionArrayClass(const OptionArrayClass&);
    OptionArrayClass& operator = (const OptionArrayClass&);
  };


  class MetricArrayOption: public OptionArrayClass<MetricType> {
  public:
    MetricArrayOption( const std::string& n,
		       std::vector<MetricType>& mp,
		       MetricType& m,
		       size_t s ):
      OptionArrayClass<MetricType>( n, mp, s ), def(m){
      TA.resize(s,m);
    };
    bool set_option( const std::string& line ) override;
    std::ostream& show_opt( std::ostream &os ) const override;
    std::ostream& show_full( std::ostream &os ) const override;
  private:
    const MetricType& def;
  };

  inline bool MetricArrayOption::set_option( const std::string& line ){
    MetricType m = UnknownMetric;
    size_t i=0;
    std::vector<std::string> res;
    bool result = TiCC::split_at( line, res, "=" ) == 2 &&
      TiCC::stringTo<MetricType>( res[1], m ) &&
      TiCC::stringTo<size_t>( res[0], i, 0, Size );
    if ( result ){
      TA[i] = m;
    }
    return result;
  }

  inline std::ostream& MetricArrayOption::show_opt( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : ";
    for ( size_t i=0; i < Size; i++ ){
      if ( TA[i] != def ){
	os << i << ":" << TiCC::toString<MetricType>(TA[i]) << ", ";
      }
    }
    return os;
  }

  inline std::ostream& MetricArrayOption::show_full( std::ostream &os ) const {
    os.width(20);
    os.setf( std::ios::left, std::ios::adjustfield );
    os << Name << " : comma separated metricvalues, [";
    bool first = true;
    for ( size_t i=0; i < Size; i++ ){
      if ( TA[i] != def ){
	if ( !first ){
	  os << ",";
	}
	else {
	  first = false;
	}
	os << i << ":" << TiCC::toString<MetricType>(TA[i]);
      }
    }
    os << "]";
    return os;
  }

  //
  // Limited Type, with min and maxVal
  //
  template <class Type>
    class OptionClassLT: public OptionClass {
    public:
    OptionClassLT( const std::string& n, Type *tp, Type t,
		   Type Min, Type Max ):OptionClass(n),
      Content( tp), minVal( Min ), maxVal( Max )
      { *Content = t; };

    virtual bool set_option( const std::string& line ) override {
      Type T;
      bool result = TiCC::stringTo<Type>( line, T, minVal, maxVal );
      if ( result ) {
	*Content = T;
      }
      return result;
    };
    virtual std::ostream& show_opt( std::ostream &os ) const override {
      os.width(20);
      os.setf( std::ios::showpoint );
      os.setf( std::ios::left, std::ios::adjustfield );
      os << Name << " : " << *Content;
      return os;
    };
    virtual std::ostream& show_full( std::ostream &os ) const override {
      os.width(20);
      os.setf( std::ios::showpoint );
      os.setf( std::ios::left, std::ios::adjustfield );
      os << Name << " :  { "
	 << minVal << " - " << maxVal << "}, [" << *Content << "]";
      return os;
    };
    private:
    Type *Content;
    Type minVal;
    Type maxVal;
    OptionClassLT(const OptionClassLT&);
    OptionClassLT& operator = (const OptionClassLT&);
  };

  using IntegerOption = OptionClassLT<int>;
  using UnsignedOption = OptionClassLT<unsigned int>;
  using SizeOption = OptionClassLT<size_t>;
  using RealOption = OptionClassLT<double>;

  enum SetOptRes { Opt_OK, Opt_Frozen, Opt_Unknown, Opt_Ill_Val};

  struct ci_less
  {
    // case-independent (ci) compare_less binary function
    struct nocase_compare
    {
      bool operator() (const unsigned char& c1, const unsigned char& c2) const {
          return tolower (c1) < tolower (c2);
      }
    };
    bool operator() (const std::string & s1, const std::string & s2) const {
      return std::lexicographical_compare
        (s1.begin(), s1.end(),   // source range
	 s2.begin(), s2.end(),   // dest range
	 nocase_compare());      // comparison
    }
  };

  class OptionTableClass {
  public:
    OptionTableClass():
      table_frozen(false){};
    OptionTableClass( const OptionTableClass& ) = delete; // forbid copies
    OptionTableClass& operator=( const OptionTableClass& ) = delete; // forbid copies
    ~OptionTableClass(){
      for ( const auto& it : global_table ){
	delete it.second;
      }
      for ( const auto& it : runtime_table ){
	delete it.second;
      }
    };
    bool Add( OptionClass *opt ){
      //      std::cerr << "Table add: " << opt->Name << std::endl;
      runtime_table[opt->Name] = opt;
      return true;
    };
    void FreezeTable(void);
    bool TableFrozen(void){ return table_frozen; };
    SetOptRes SetOption( const std::string& );
    void Show_Settings( std::ostream& ) const;
    void Show_Options( std::ostream& ) const;
  private:
    bool table_frozen;
    std::map<std::string,OptionClass *,ci_less> runtime_table;
    std::map<std::string,OptionClass *,ci_less> global_table;
    inline OptionClass *look_up( const std::string&, bool & );
  };

  inline void OptionTableClass::FreezeTable(void){
    global_table = runtime_table;
    runtime_table.clear();
    table_frozen = true;
  }

  inline void OptionTableClass::Show_Settings( std::ostream& os ) const{
    for ( const auto& it: global_table ){
      it.second->show_opt( os ) << std::endl;
    }
    for ( const auto& it: runtime_table ){
      it.second->show_opt( os ) << std::endl;
    }
  }

  inline void OptionTableClass::Show_Options( std::ostream& os ) const {
    for ( const auto& it: global_table ){
      it.second->show_full( os ) << std::endl;
    }
    for ( const auto& it: runtime_table ){
      it.second->show_full( os ) << std::endl;
    }
  }

  inline void split_line( const std::string& line,
			  std::string& name,
			  std::string& value ){
    std::vector<std::string> results;
    size_t i = TiCC::split_at( line, results, ":" );
    switch (i){
    case 2:
      name = TiCC::trim(results[0]);
      // fallthrough
    case 1:
      value = TiCC::trim(results[1]);
    default:
      break;
    }
  }

  inline OptionClass *OptionTableClass::look_up( const std::string& option_name,
						 bool &runtime ){
    //    std::cerr << "lookup: " << option_name << std::endl;
    const auto itr = runtime_table.find( option_name );
    if ( itr != runtime_table.end() ){
      runtime = true;
      //      std::cerr << "FOUND: runtime= " << option_name << std::endl;
      return itr->second;
    }
    else {
      const auto itg = global_table.find( option_name );
      if ( itg != global_table.end() ){
	runtime = table_frozen;
	//	std::cerr << "FOUND global= " << option_name << std::endl;
	return itg->second;
      }
    }
    return NULL;
  }

  inline SetOptRes OptionTableClass::SetOption( const std::string& line ){
    SetOptRes result = Opt_OK;
    bool runtime = false;
    std::string option_name;
    std::string value;
    split_line( line, option_name, value );
    OptionClass *option = look_up( option_name, runtime );
    if ( option ){
      if ( !runtime ){
	result = Opt_Frozen; // may not be changed at this stage
      }
      else if ( !option->set_option( value ) ){
	result = Opt_Ill_Val; // illegal value
      }
    }
    else {
      result = Opt_Unknown; // What the hell ???
    }
    return result;
  }


}

#endif

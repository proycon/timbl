/*
  $Id$
  $URL$

  Copyright (c) 1998 - 2011
  ILK  -  Tilburg University
  CNTS -  University of Antwerp
 
  This file is part of Timbl

  Timbl is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  Timbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.

  For questions and suggestions, see:
      http://ilk.uvt.nl/software.html
  or send mail to:
      Timbl@uvt.nl
*/

#ifndef STATISTICS_H
#define STATISTICS_H

namespace Timbl {
  class ConfusionMatrix: public MsgClass {
    size_t size;
    std::vector<std::vector<size_t> > mat;
  public:
    ConfusionMatrix( size_t );  
    virtual ~ConfusionMatrix();
    void Increment( const TargetValue*, const TargetValue* );
    void Print( std::ostream&, const Target * ) const;
    void FScore( std::ostream&, const Target *, bool ) const;
    void merge( const ConfusionMatrix * );
  };
  
  class StatisticsClass {
  public:
  StatisticsClass(): _data(0), _skipped(0), _correct(0),
      _tieOk(0), _tieFalse(0), _exact(0) {};
    void clear() { _data =0; _skipped = 0; _correct = 0; 
      _tieOk = 0; _tieFalse = 0; _exact = 0; };
    void addLine() { ++_data; }
    void addSkipped() { ++_skipped; }
    void addCorrect() { ++_correct; }
    void addTieCorrect() { ++_tieOk; }
    void addTieFailure() { ++_tieFalse; }
    void addExact() { ++_exact; }
    unsigned int dataLines() const { return _data; };
    unsigned int skippedLines() const { return _skipped; };
    unsigned int totalLines() const { return _data + _skipped; };
    unsigned int testedCorrect() const { return _correct; };
    unsigned int tiedCorrect() const { return _tieOk; };
    unsigned int tiedFailure() const { return _tieFalse; };
    unsigned int exactMatches() const { return _exact; };
    void merge( const StatisticsClass& );
  private:
    unsigned int _data;
    unsigned int _skipped;
    unsigned int _correct;
    unsigned int _tieOk;
    unsigned int _tieFalse;
    unsigned int _exact;
  };

}
#endif

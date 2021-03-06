#ifndef ControlPointV0003_h
#define ControlPointV0003_h
/**
 * @file
 * $Revision: 1.9 $
 * $Date: 2009/07/15 17:33:52 $
 *
 *   Unless noted otherwise, the portions of Isis written by the USGS are
 *   public domain. See individual third-party library and package descriptions
 *   for intellectual property information, user agreements, and related
 *   information.
 *
 *   Although Isis has been used by the USGS, no warranty, expressed or
 *   implied, is made by the USGS as to the accuracy and functioning of such
 *   software and related material nor shall the fact of distribution
 *   constitute any such warranty, and no responsibility is assumed by the
 *   USGS in connection therewith.
 *
 *   For additional information, launch
 *   $ISISROOT/doc//documents/Disclaimers/Disclaimers.html
 *   in a browser or see the Privacy &amp; Disclaimers page on the Isis website,
 *   http://isis.astrogeology.usgs.gov, and the USGS privacy and disclaimers on
 *   http://www.usgs.gov/privacy.html.
 */

#include <QSharedPointer>

#include "ControlPointFileEntryV0002.pb.h"

namespace Isis {
  class ControlPointV0002;
  class PvlObject;
  class PvlContainer;

  /**
   * @brief A container for the information stored in a version 3 and 4 ControlPoint.
   *
   * A wrapper around the version 3 and 4 protobuf serialization of a ControlPoint. It allows for
   * reading ControlPoints serialized as both PvlObjects and protobuf messages. It also allows
   * for upgrading version 2 ControlPoints to version 3 and 4 ControlPoints.
   *
   * The version 3 and 4 binary serialization of ControlPoint use the same protobuf message, so
   * this class works with both versions. The difference between the version 3 and 4 Pvl
   * serializations is Ground and Tie points were renamed to Fixed and Free respectively.
   * This is sufficiently minor that it is handled in the pvl constructor.
   *
   * In the Pvl format, control points are represented by objects contained in the
   * ControlNetwork object. Control measures are represented by groups
   * contained in the control point objects.
   *
   * <b>Valid Control Point Keywords</b>
   *
   * <ul>
   *   <li><em>PointId:</em> The point ID string</li>
   *   <li><em>ChooserName:</em> The name of the application or user that last
   *       modified the point</li>
   *   <li><em>DateTime:</em> The date and time of the last modification to the
   *       point</li>
   *   <li><em>AprioriXYZSource:</em> What type of source the apriori ground
   *       point was calculated from. Options:
   *       <ul>
   *           <li>None</li>
   *           <li>User</li>
   *           <li>AverageOfMeasures</li>
   *           <li>Reference</li>
   *           <li>Basemap</li>
   *           <li>BundleSolution</li>
   *       </ul></li>
   *   <li><em>AprioriXYZSourceFile:</em> The name of the file that the apriori
   *       ground point was calculated from</li>
   *   <li><em>AprioriRadiusSource:</em> What type of source the apriori point
   *       radius was calculated from. Options:
   *       <ul>
   *           <li>None</li>
   *           <li>User</li>
   *           <li>AverageOfMeasures</li>
   *           <li>Ellipsoid</li>
   *           <li>DEM</li>
   *           <li>BundleSolution</li>
   *       </ul></li>
   *   <li><em>AprioriRadiusSourceFile:</em> The name of the file that the
   *       apriori point radius was calculated from</li>
   *   <li><em>JigsawRejected:</em> If the point was rejected by a bundle
   *       adjustment</li>
   *   <li><em>EditLock:</em> If the point is locked out of editing</li>
   *   <li><em>Ignore:</em> If the point will be ignored</li>
   *   <li><em>AprioriX:</em> The body fixed X coordinate of the a priori
   *       ground point in meters</li>
   *   <li><em>AprioriY:</em> The body fixed Y coordinate of the a priori
   *       ground point in meters</li>
   *   <li><em>AprioriZ:</em> The body fixed Z coordinate of the a priori
   *       ground point in meters</li>
   *   <li><em>AdjustedX:</em> The body fixed X coordinate of the adjusted
   *       ground point in meters</li>
   *   <li><em>AdjustedY:</em> The body fixed Y coordinate of the adjusted
   *       ground point in meters</li>
   *   <li><em>AdjustedZ:</em> The body fixed Z coordinate of the adjusted
   *       ground point in meters</li>
   *   <li><em>LatitudeConstrained:</em> If the latitude of the ground point
   *       is constrained</li>
   *   <li><em>LongitudeConstrained:</em> If the longitude of the ground point
   *       is constrained</li>
   *   <li><em>RadiusConstrained:</em> If the radius of the ground point
   *       is constrained</li>
   *   <li><em>PointType:</em> What type of point it is. Options:
   *       <ul>
   *           <li>Fixed</li>
   *           <li>Ground</li>
   *           <li>Constrained</li>
   *           <li>Free</li>
   *           <li>Tie</li>
   *       </ul></li>
   *   <li><em>AprioriCovarianceMatrix:</em> A six element vector corresponding
   *       to the upper triangle; elements (0,0), (0,1), (0,2), (1,1), (1,2),
   *       and (2,2); of the 3x3, symmetric covariance matrix for
   *       the rectangular, a priori ground point.</li>
   *   <li><em>AdjustedCovarianceMatrix:</em> A six element vector corresponding
   *       to the upper triangle; elements (0,0), (0,1), (0,2), (1,1), (1,2),
   *       and (2,2); of the 3x3, symmetric covariance matrix for
   *       the rectangular, adjusted ground point.</li>
   * </ul>
   *
   * <b>Valid Control Measure Keywords</b>
   *
   * <ul>
   *   <li><em>SerialNumber:</em> The serial number of the cube the measure
   *       is from</li>
   *   <li><em>ChooserName:</em> The name of the application or user who last
   *       modified the measure</li>
   *   <li><em>DateTime:</em> The date and time of the last modification</li>
   *   <li><em>Diameter:</em> If the measure was selected from a crater, this
   *       is the diameter of the crater in meters</li>
   *   <li><em>EditLock:</em> If the measure is locked out of editing</li>
   *   <li><em>Ignore:</em> If the measure will be ignored</li>
   *   <li><em>JigsawRejected:</em> If the measure was rejected during a
   *       bundle adjustment</li>
   *   <li><em>AprioriSample:</em> The a priori sample</li>
   *   <li><em>AprioriLine:</em> The a priori line</li>
   *   <li><em>SampleSigma:</em> The standard deviation of the sample
   *       measurement</li>
   *   <li><em>LineSigma:</em> The standard deviation of the line
   *       measurement</li>
   *   <li><em>Sample:</em> The adjusted sample</li>
   *   <li><em>Line:</em> The adjusted line</li>
   *   <li><em>SampleResidual:</em> The difference between the a priori and
   *       adjusted sample</li>
   *   <li><em>LineResidual:</em> The difference between the a priori and
   *       adjusted line</li>
   *   <li><em>Reference:</em> If the measure is the reference measure for
   *       its point</li>
   *   <li><em>MeasureType:</em> What type of measure it is. Options:
   *       <ul>
   *           <li>candidate</li>
   *           <li>manual</li>
   *           <li>registeredpixel</li>
   *           <li>registeredsubpixel</li>
   *       </ul></li>
   * </ul>
   *
   * @ingroup ControlNetwork
   *
   * @author 2017-12-14 Jesse Mapel
   *
   * @internal
   *   @history 2017-12-14 Jesse Mapel - Original version.
   *   @history 2017-12-21 Jesse Mapel - Added support for measure log data.
   *   @history 2017-12-21 Adam Goins - Changed Pvl constructor to take PvlObject.
   *   @history 2017-12-21 Adam Goins - Changed Pvl constructor to not used
   *                           the deprecated "ToProtocolBuffer()" call from
   *                           ControlMeasureLogData.
   *   @history 2018-01-03 Jesse Mapel - Improved documentation.
   *   @history 2017-01-27 Jesse Mapel - More documentation improvements.
   */
  class ControlPointV0003 {
    public:
      ControlPointV0003(PvlObject &pointObject);
      ControlPointV0003(QSharedPointer<ControlPointFileEntryV0002> pointData);
      ControlPointV0003(ControlPointV0002 &oldPoint);

      const ControlPointFileEntryV0002 &pointData();

    private:
      /**
       * Default constructor. Intentionally un-implemented.
       */
      ControlPointV0003();
      /**
       * Copy constructor. Intentionally un-implemented.
       *
       * @param other The other ControlPointV0003 to copy from.
       */
      ControlPointV0003(const ControlPointV0003 &other);
      /**
       * Assignment operator. Intentionally un-implemented.
       *
       * @param other The other ControlPointV0003 to assign from.
       *
       * @return @b ControlPointV0003& A reference to this after assignment.
       */
      ControlPointV0003 &operator=(const ControlPointV0003 &other);

      // methods for converting from Pvl to protobuf
      void copy(PvlContainer &container,
                QString keyName,
                QSharedPointer<ControlPointFileEntryV0002> point,
                void (ControlPointFileEntryV0002::*setter)(bool));
      void copy(PvlContainer &container,
                QString keyName,
                QSharedPointer<ControlPointFileEntryV0002> point,
                void (ControlPointFileEntryV0002::*setter)(double));
      void copy(PvlContainer &container,
                QString keyName,
                QSharedPointer<ControlPointFileEntryV0002> point,
                void (ControlPointFileEntryV0002::*setter)(const std::string&));
      void copy(PvlContainer &container,
                QString keyName,
                ControlPointFileEntryV0002_Measure &measure,
                void (ControlPointFileEntryV0002_Measure::*setter)(bool));
      void copy(PvlContainer &container,
                QString keyName,
                ControlPointFileEntryV0002_Measure &measure,
                void (ControlPointFileEntryV0002_Measure::*setter)(double));
      void copy(PvlContainer &container,
                QString keyName,
                ControlPointFileEntryV0002_Measure &measure,
                void (ControlPointFileEntryV0002_Measure::*setter)(const std::string &));

      QSharedPointer<ControlPointFileEntryV0002> m_pointData; /**< protobuf container that holds
                                                                   information used to create a
                                                                   control point.*/
  };
}

#endif

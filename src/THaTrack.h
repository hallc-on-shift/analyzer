#ifndef ROOT_THaTrack
#define ROOT_THaTrack

//////////////////////////////////////////////////////////////////////////
//
// THaTrack
//
//////////////////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TMath.h"

class TClonesArray;
class THaPIDinfo;
class THaVertex;
class THaSpectrometer;
class THaTrackingDetector;
class THaTrackID;
class THaCluster;

class THaTrack : public TObject {

public:

  THaTrack() : fP(0.0), fPx(0.0), fPy(0.0), fPz(0.0), fTheta(0.0), fPhi(0.0),
    fX(0.0), fY(0.0), fClusters(NULL), fPIDinfo(NULL), fVertex(NULL),
    fSpectrometer(NULL), fID(NULL), fFlag(0) {}
  THaTrack( Double_t p, Double_t theta, Double_t phi, Double_t x, Double_t y,
	    THaSpectrometer* s=NULL, THaPIDinfo* pid=NULL, 
	    THaVertex* vertex=NULL, THaTrackID* id=NULL );
  virtual ~THaTrack();

  
  Int_t             AddCluster( THaCluster* c );
  void              Clear( Option_t* opt="" );
  THaTrackID*       GetID() const                  { return fID; }
  UInt_t            GetFlag() const                { return fFlag; }
  Double_t          GetP()  const                  { return fP; }
  Double_t          GetPx() const                  { return fPx; }
  Double_t          GetPy() const                  { return fPy; }
  Double_t          GetPz() const                  { return fPz; }
  Double_t          GetX()  const                  { return fX; }
  Double_t          GetY()  const                  { return fY; }
  Double_t          GetX( Double_t z ) const;
  Double_t          GetY( Double_t z ) const;
  Double_t          GetTheta() const               { return fTheta; }
  Double_t          GetPhi() const                 { return fPhi; }

  Double_t       GetDX()        const { return fDX; }
  Double_t       GetDY()        const { return fDY; }
  Double_t       GetDTheta()    const { return fDTheta; }
  Double_t       GetDPhi()      const { return fDPhi; } 
  Double_t       GetRX()        const { return fRX; }
  Double_t       GetRY()        const { return fRY; }
  Double_t       GetRTheta()    const { return fRTheta; }
  Double_t       GetRPhi()      const { return fRPhi; } 
  Double_t       GetTX()        const { return fTX; }
  Double_t       GetTY()        const { return fTY; }
  Double_t       GetTTheta()    const { return fTTheta; }
  Double_t       GetTPhi()      const { return fTPhi; }
  Double_t       GetDp()        const { return fDp; }

  void              Print( Option_t* opt="" ) const;
  void              SetID( THaTrackID* id )        { fID = id; }
  void              SetFlag( UInt_t flag )         { fFlag = flag; }
  void              SetMomentum( Double_t p, Double_t theta, Double_t phi );
  void              SetPosition( Double_t x, Double_t y );
  void              Set( Double_t p, Double_t theta, Double_t phi, 
			 Double_t x, Double_t y );
  void              SetR( Double_t x, Double_t y,
			  Double_t theta, Double_t phi );
  void              SetD( Double_t x, Double_t y,
			  Double_t theta, Double_t phi );
  void              SetTarget( Double_t x, Double_t y,
			  Double_t theta, Double_t phi );
  void              SetDp(Double_t dp) { fDp = dp; }

  void              SetCreator( THaTrackingDetector* d ) 
                                                   { fCreator = d; }
  void              SetPIDinfo(  THaPIDinfo* pid ) { fPIDinfo  = pid; }
  void              SetSpectrometer( THaSpectrometer* s )
                                                   { fSpectrometer = s; }
  void              SetVertex( THaVertex* v )      { fVertex   = v; }

  THaTrackingDetector* GetCreator()    const       { return fCreator; }
  TList*             GetClusters()     const       { return fClusters; }
  THaSpectrometer*   GetSpectrometer() const       { return fSpectrometer; }
  THaPIDinfo*        GetPIDinfo()      const       { return fPIDinfo; }
  THaVertex*         GetVertex()       const       { return fVertex; }

protected:

  Double_t          fP;              // momentum (GeV)
  Double_t          fPx;             // x momentum component (GeV)
  Double_t          fPy;             // y momentum component (GeV)
  Double_t          fPz;             // z momentum component (GeV)

  // FIXME: should these coordinates all have their own structures?
  Double_t          fTheta;          // Tangent of TRANSPORT Theta (x')
  Double_t          fPhi;            // Tangent of TRANSPORT Phi (y')
  Double_t          fX;              // x position in focal plane (m)
  Double_t          fY;              // y position (m)

  // coordinates in the rotated TRANSPORT system
  Double_t fRX;     // x position in focal plane
  Double_t fRY;     // y position in focal plane
  Double_t fRTheta; // Tangent of TRANSPORT Theta (x')
  Double_t fRPhi;   // Tangent of TRANSPORT Phi (y')

  // coordinates in the target system
  Double_t fTX;     // x position at target
  Double_t fTY;     // y position at target
  Double_t fTTheta; // deviation of velocity in x direction
  Double_t fTPhi;   // deviation of velocity in y direction

  // coordinates in the detector system
  Double_t fDX;     // x position in DCS
  Double_t fDY;     // y position in DCS
  Double_t fDTheta; // Tangent of DCS Theta 
  Double_t fDPhi;   // Tangent of DCS Phi 

  Double_t fDp;     // dp/p_center -- fractional change in momentum
  //Double_t fPmom; == fP (MeV/c)


  TList*            fClusters;       // clusters of this track
  THaPIDinfo*       fPIDinfo;        // particle ID information for this track
  THaVertex*        fVertex;         // reconstructed vertex quantities
  THaSpectrometer*  fSpectrometer;   // spectrometer this track belongs to
  THaTrackingDetector* fCreator;     // Detector creating this track
  THaTrackID*       fID;             // Track identifier
  UInt_t            fFlag;           // Status flag

  void              CalcPxyz();

private:

  ClassDef(THaTrack,0)  //A track in the focal plane
};

//__________________ inlines __________________________________________________
inline
void THaTrack::CalcPxyz()
{
  // Internal function to compute momentum components.

  fPz     = fP/TMath::Sqrt(1.0+fTheta*fTheta+fPhi*fPhi);
  fPx     = fPz*fTheta;
  fPy     = fPz*fPhi;
}

//_____________________________________________________________________________
inline
Double_t THaTrack::GetX( Double_t z ) const
{
  // Return x position at distance z from the focal plane,
  // assuming that the track is not deflected in the detector region.

  return fX + z*fTheta;
}

//_____________________________________________________________________________
inline
Double_t THaTrack::GetY( Double_t z ) const
{
  // Return y position at distance z from the focal plane,
  // assuming that the track is not deflected in the detector region.

  return fY + z*fPhi;
}

//_____________________________________________________________________________
inline
void THaTrack::SetMomentum( Double_t p, Double_t theta, Double_t phi )
{
  fP      = p;
  fTheta  = theta;
  fPhi    = phi;
  CalcPxyz();
}

//_____________________________________________________________________________
inline
void THaTrack::SetPosition( Double_t x, Double_t y )
{
  fX = x;
  fY = y;
}

//_____________________________________________________________________________
inline
void THaTrack::Set( Double_t p, Double_t theta, Double_t phi,
			   Double_t x, Double_t y )
{
  SetMomentum( p, theta, phi );
  SetPosition( x, y );
}

//_____________________________________________________________________________
inline
void THaTrack::SetD( Double_t x, Double_t y, Double_t theta, Double_t phi )
{
  // set the coordinates in the rotated focal-plane frame
  fDX = x;
  fDY = y;
  fDTheta = theta;
  fDPhi = phi;
}

//_____________________________________________________________________________
inline
void THaTrack::SetR( Double_t x, Double_t y, Double_t theta, Double_t phi )
{
  // set the coordinates in the rotated focal-plane frame
  fRX = x;
  fRY = y;
  fRTheta = theta;
  fRPhi = phi;
}

//_____________________________________________________________________________
inline
void THaTrack::SetTarget( Double_t x, Double_t y, Double_t theta, Double_t phi )
{
  // set the coordinates in the target frame
  fTX = x;
  fTY = y;
  fTTheta = theta;
  fTPhi = phi;
}
#endif

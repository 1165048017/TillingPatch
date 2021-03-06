/************************************************************************\

  Copyright 1997 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software
  and its documentation for educational, research and non-profit
  purposes, without fee, and without a written agreement is
  hereby granted, provided that the above copyright notice and
  the following three paragraphs appear in all copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL
  HILL BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL,
  INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
  ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
  EVEN IF THE UNIVERSITY OF NORTH CAROLINA HAVE BEEN ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGES.


  Permission to use, copy, modify and distribute this software
  and its documentation for educational, research and non-profit
  purposes, without fee, and without a written agreement is
  hereby granted, provided that the above copyright notice and
  the following three paragraphs appear in all copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
  BASIS, AND THE UNIVERSITY OF NORTH CAROLINA HAS NO OBLIGATION
  TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
  MODIFICATIONS.


   --------------------------------- 
  |Please send all BUG REPORTS to:  |
  |                                 |
  |   geom@cs.unc.edu               |
  |                                 |
   ---------------------------------
  
     
  The authors may be contacted via:

  US Mail:  A. Pattekar/J. Cohen/T. Hudson/S. Gottschalk/M. Lin/D. Manocha
            Department of Computer Science
            Sitterson Hall, CB #3175
            University of N. Carolina
            Chapel Hill, NC 27599-3175
            
  Phone:    (919)962-1749
            
  EMail:    geom@cs.unc.edu

\************************************************************************/

/************************************************************************\
Filename: VCollide.H
--
Description: This file declares the classes - VCollide and VCReport.

\************************************************************************/


#ifndef VCOLLIDE_H
#define VCOLLIDE_H

//error codes returned by VCollide API.
//these are multiply defined in the file VInternal.C
//so, any changes to these need to be reflected in all three places.
const int VC_ERR_INVALID_ID            = -4; //invalid id was passed to the
                                             //routine.
const int VC_ERR_EMPTY_OBJECT          = -3;//EndObject called without adding
                                             //adding any triangles.
const int VC_ERR_CALL_OUT_OF_SEQUENCE  = -2; //calls out of sequence.
const int VC_ERR                       = -1; //some other error.
const int VC_OK                        =  1; //No error.

//multiply defined in files VInternal.C
const int VC_ALL_CONTACTS  = 1;  // want RAPID to return all contact 
                                 // information between each object pair.
const int VC_FIRST_CONTACT = 2;  // want RAPID to return only first contact
                                 // between each object pair.

class VCInternal; //declared in file VInternal.H


/************************************************************************
Class: VCReport
--
Description: Used for reporting collisions.

\************************************************************************/
//multiply defined in file VInternal.C
#ifndef _VCREPORT
#define _VCREPORT

class VCObjPair;  //declared in file VInternal.C


class VCReport
{
    friend class VCInternal;

private:

    int num_obj_pairs;    // number of intersecting object-pairs.
    VCObjPair *obj_pair;  // an array of the object pairs.

public:

    VCReport();  // constructor
    ~VCReport(); // destructor   

    int numObjPairs();
	// returns the number of pairs of objects that
	// are in contact.

    int obj1ID( int obj_pair_num );
	// returns the ID of the first object in the 
	// specified object-pair.

    int obj2ID( int obj_pair_num );
	// returns the ID of the second object in the 
	// specified object-pair.

    int numTriPairs( int obj_pair_num );
	// returns the number of pairs of triangles that are
	// in contact between the specified pair of objects.
	// This is useful only if VCollide::Collide() was
	// called with VC_ALL_CONTACTS.
	// If VCollide::Collide() was called with,
	// VC_FIRST_CONTACT, then numTriPairs() always return 0.

    int tri1ID( int obj_pair_num, int tri_pair_num );
	// returns the ID of the first triangle in the 
	// specified triangle-pair. This triangle belongs
	// to the first object in the specified object-pair.
	// Used only if VCollide::Collide() was called
	// with VC_ALL_CONTACTS.

    int tri2ID( int obj_pair_num, int tri_pair_num );
	// returns the ID of the second triangle in the 
	// specified triangle-pair. This triangle belongs
	// to the second object in the specified object-pair.
	// Used only if VCollide::Collide() was called
	// with VC_ALL_CONTACTS.
};


#endif


/************************************************************************
Class: VCollide
--
Description: This implements the VCollide API. It is just the
             user interface and hides all the implementation
             details. Implementation details can be found in the
             class VCInternal. The member functions of the class
             VCollide just make calls to the corresponding member
             functions of class VCInternal.

\************************************************************************/

class VCollide
{
private:  
  VCInternal *vcint;
  
public:
  VCollide();             //constructor
  ~VCollide();            //destructor
  
  int NewObject(int *id); //create a new object in the database.
  int AddTri(double v1[3], double v2[3], double v3[3], int tri_id = 0); 
			  //insert the geometry.

  int EndObject(void);    //tell VCollide that inserting the 
                          //geometry is complete.
  int UpdateTrans(int id, double trans[4][4]);
                          //update the transformation matrix of
                          //the object.
  int ActivateObject(int id);          //activate for collision detection.
  int DeactivateObject(int id);        //deactivate from collision detection.
  int ActivatePair(int id1, int id2);  //activate the pair.
  int DeactivatePair(int id1, int id2);//deactivate the pair.

  int DeactivatePairAll();/*deactivate the pair. */
  int DeleteObject(int id); //delete the object from the database.

  int Collide( VCReport *report, int flag = VC_FIRST_CONTACT);
  // perform collision detection and return a report.
    // The default flag is VC_FIRST_CONTACT, 
    // flag can also be VC_ALL_CONTACTS.
};


#endif

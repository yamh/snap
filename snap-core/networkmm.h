#ifndef NETWORKMM_H
#define NETWORKMM_H
class TNEANetMM;
/// Pointer to a directed attribute multigraph (TNEANet)
typedef TPt<TNEANetMM> PNEANetMM;

//#//////////////////////////////////////////////
/// Directed multigraph with node edge attributes. ##TNEANet::Class
class TNEANetMM : public TNEANet {
public:
  typedef TNEANetMM TNetMM;
  typedef TPt<TNEANetMM> PNetMM;
public:
  class TNodeMM : TNEANet::TNode {
  private:
    TInt Id;
    TIntV InEIdV, OutEIdV;
  public:
    TNode() : Id(-1), InEIdV(), OutEIdV() { }
    TNode(const int& NId) : Id(NId), InEIdV(), OutEIdV() { }
    TNode(const TNode& Node) : Id(Node.Id), InEIdV(Node.InEIdV), OutEIdV(Node.OutEIdV) { }
    TNode(TSIn& SIn) : Id(SIn), InEIdV(SIn), OutEIdV(SIn) { }
    void Save(TSOut& SOut) const { Id.Save(SOut); InEIdV.Save(SOut); OutEIdV.Save(SOut); }
    int GetId() const { return Id; }
    int GetDeg() const { return GetInDeg() + GetOutDeg(); }
    int GetInDeg() const { return InEIdV.Len(); }
    int GetOutDeg() const { return OutEIdV.Len(); }
    int GetInEId(const int& EdgeN) const { return InEIdV[EdgeN]; }
    int GetOutEId(const int& EdgeN) const { return OutEIdV[EdgeN]; }
    int GetNbrEId(const int& EdgeN) const { return EdgeN<GetOutDeg()?GetOutEId(EdgeN):GetInEId(EdgeN-GetOutDeg()); }
    bool IsInEId(const int& EId) const { return InEIdV.SearchBin(EId) != -1; }
    bool IsOutEId(const int& EId) const { return OutEIdV.SearchBin(EId) != -1; }
    friend class TNEANet;
  };
  class TEdgeMM {
  private:
    TInt Id, SrcNId, DstNId, SrcNTypeId, DstNTypeId;
  public:
    TEdgeMM() : Id(-1), SrcNId(-1), DstNId(-1), SrcNTypeId(-1), DstNTypeId(-1) { }
    TEdgeMM(const int& EId, const int& SourceNId, const int& DestNId, const int& SourceNTypeId, const int& DestNTypeId) : 
      Id(EId), SrcNId(SourceNId), DstNId(DestNId), SrcNTypeId(SourceNTypeId), DstNTypeId(DestNTypeId) { }
    TEdgeMM(const TEdge& Edge) : Id(Edge.Id), SrcNId(Edge.SrcNId), DstNId(Edge.DstNId) { }
    TEdgeMM(TSIn& SIn) : Id(SIn), SrcNId(SIn), DstNId(SIn), SrcNTypeId(SIn), DstNTypeId(SIn) { }
    void Save(TSOut& SOut) const { Id.Save(SOut); SrcNId.Save(SOut); DstNId.Save(SOut); SrcNTypeId(-1).Save(SOut); DstNTypeId.Save(SOut); }
    int GetId() const { return Id; }
    int GetSrcNId() const { return SrcNId; }
    int GetDstNId() const { return DstNId; }
    int GetSrcNTypeId() const { return SrcNTypeId; }
    int GetDstNTypeId() const { return DstNTypeId; }
    friend class TNEANetMM;
  };

/*private:
  TNode& GetNode(const int& NId) { return NodeH.GetDat(NId); }
  const TNode& GetNode(const int& NId) const { return NodeH.GetDat(NId); }
  TEdge& GetEdge(const int& EId) { return EdgeH.GetDat(EId); }
  const TEdge& GetEdge(const int& EId) const { return EdgeH.GetDat(EId); }

  /// Get Int node attribute val.  If not a proper attr, return default.
  TInt GetIntAttrDefaultN(const TStr& attribute) const { return IntDefaultsN.IsKey(attribute) ? IntDefaultsN.GetDat(attribute) : (TInt) TInt::Mn; }
  /// Get Str node attribute val.  If not a proper attr, return default.
  TStr GetStrAttrDefaultN(const TStr& attribute) const { return StrDefaultsN.IsKey(attribute) ? StrDefaultsN.GetDat(attribute) : (TStr) TStr::GetNullStr(); }
  /// Get Flt node attribute val.  If not a proper attr, return default.
  TFlt GetFltAttrDefaultN(const TStr& attribute) const { return FltDefaultsN.IsKey(attribute) ? FltDefaultsN.GetDat(attribute) : (TFlt) TFlt::Mn; }
  /// Get Int edge attribute val.  If not a proper attr, return default.
  TInt GetIntAttrDefaultE(const TStr& attribute) const { return IntDefaultsE.IsKey(attribute) ? IntDefaultsE.GetDat(attribute) : (TInt) TInt::Mn; }
  /// Get Str edge attribute val.  If not a proper attr, return default.
  TStr GetStrAttrDefaultE(const TStr& attribute) const { return StrDefaultsE.IsKey(attribute) ? StrDefaultsE.GetDat(attribute) : (TStr) TStr::GetNullStr(); }
  /// Get Flt edge attribute val.  If not a proper attr, return default.
  TFlt GetFltAttrDefaultE(const TStr& attribute) const { return FltDefaultsE.IsKey(attribute) ? FltDefaultsE.GetDat(attribute) : (TFlt) TFlt::Mn; }
*/
private:
  /*TCRef CRef;
  TInt MxNId, MxEId;
  THash<TInt, TNode> NodeH;
  THash<TInt, TEdge> EdgeH;
  /// KeyToIndexType[N|E]: Key->(Type,Index).
  TStrIntPrH KeyToIndexTypeN, KeyToIndexTypeE;

  THash<TStr, TInt> IntDefaultsN, IntDefaultsE;
  THash<TStr, TStr> StrDefaultsN, StrDefaultsE;
  THash<TStr, TFlt> FltDefaultsN, FltDefaultsE;
  TVec<TIntV> VecOfIntVecsN, VecOfIntVecsE;
  TVec<TStrV> VecOfStrVecsN, VecOfStrVecsE;
  TVec<TFltV> VecOfFltVecsN, VecOfFltVecsE;
  enum { IntType, StrType, FltType };*/
  THash<TPair<TInt, TInt>, TEdgeMM> TypeEdgeH; //(Src Type Id, EId) -> edge class
  TVec<TVec<TIntV> > OutEdgeV;
  TVec<TVec<TIntV> > InEdgeV;
  TInt MxTypeEId;
  TInt NTypeId;
public:
  TNEANetMM() : TNEANet(), TypeEdgeH(), OutEdgeV(), InEdgeV(), MxTypeEId(0), NTypeId(-1) { }
  TNEANetMM(const int& TypeId) : TNEANet(), TypeEdgeH(), OutEdgeV(), InEdgeV(), MxTypeEId(0), NTypeId(TypeId) { }
  /// Constructor that reserves enough memory for a graph of nodes and edges.
  explicit TNEANetMM(const int& Nodes, const int& Edges) : TNEANet(Nodes, Edges),
    TypeEdgeH(), OutEdgeV(), InEdgeV(), MxTypeEId(0), NTypeId(-1) { }
  explicit TNEANetMM(const int& Nodes, const int& Edges, const int& TypeId) : TNEANet(Nodes, Edges),
    TypeEdgeH(), OutEdgeV(), InEdgeV(), MxTypeEId(0), NTypeId(TypeId) { }
  TNEANetMM(const TNEANetMM& Graph) :  TNEANet(Graph), TypeEdgeH(Graph.TypeEdgeH),
    OutEdgeV(Graph.OutEdgeV), InEdgeV(Graph.InEdgeV), MxTypeEId(Graph.MxTypeEId), NTypeId(Graph.NTypeId) { }
  /// Constructor for loading the graph from a (binary) stream SIn.
  TNEANetMM(TSIn& SIn) : TNEANet(SIn), TypeEdgeH(SIn), OutEdgeV(SIn), InEdgeV(SIn), MxTypeEId(SIn), NTypeId(SIn) { }

  //Make these functions virtual

  /// Saves the graph to a (binary) stream SOut.
  void Save(TSOut& SOut) const {
    TNEANet::Save(SOut); TypeEdgeH.Save(SOut); OutEdgeV.Save(SOut);
    InEdgeV.Save(SOut); MxTypeEId.Save(SOut); NTypeId.Save(SOut); }
  /// Static cons returns pointer to graph. Ex: PNEANet Graph=TNEANet::New().
  static PNEANetMM New() { return PNEANetMM(new TNEANetMM()); }
  /// Static constructor that returns a pointer to the graph and reserves enough memory for Nodes nodes and Edges edges. ##TNEANet::New
  static PNEANetMM New(const int& Nodes, const int& Edges) { return PNEANetMM(new TNEANetMM(Nodes, Edges)); }
  /// Static constructor that loads the graph from a stream SIn and returns a pointer to it.
  static PNEANetMM Load(TSIn& SIn) { return PNEANetMM(new TNEANetMM(SIn)); }



  /// Returns an ID that is larger than any edge ID in the network.
  int GetMxTypeEId() const { return MxTypeEId; }

  // Returns the number of edges in the graph.
  //int GetEdges() const { return EdgeH.Len(); }
  /// Adds an edge with ID EId between node IDs SrcNId and DstNId to the graph. ##TNEANet::AddEdge
  int AddEdge(const int& SrcNId, const int& SrcNTypeId, const int& DstNId, const int& DstNTypeId, int EId=-1);
  /// Adds an edge between EdgeI.GetSrcNId() and EdgeI.GetDstNId() to the graph.
  //int AddEdge(const TEdgeI& EdgeI) { return AddEdge(EdgeI.GetSrcNId(), EdgeI.GetDstNId(), EdgeI.GetId()); }
  /// Deletes an edge with edge ID EId from the graph.
  void DelEdge(const int& EId);
  /// Deletes all edges between node IDs SrcNId and DstNId from the graph. ##TNEANet::DelEdge
  void DelEdge(const int& SrcNId, const int& SrcNTypeId, const int& DstNId, const int& DstNTypeId);
  /// Tests whether an edge with edge ID EId exists in the graph.
  //bool IsEdge(const int& EId) const { return EdgeH.IsKey(EId); }
  /// Tests whether an edge between node IDs SrcNId and DstNId exists in the graph.
  //bool IsEdge(const int& SrcNId, const int& DstNId, const bool& IsDir = true) const { int EId; return IsEdge(SrcNId, DstNId, EId, IsDir); }
  /// Tests whether an edge between node IDs SrcNId and DstNId exists in the graph. if an edge exists, return its edge ID in EId
  //bool IsEdge(const int& SrcNId, const int& DstNId, int& EId, const bool& IsDir = true) const;
  /// Returns an edge ID between node IDs SrcNId and DstNId, if such an edge exists. Otherwise, return -1.
  int GetEId(const int& SrcNId, const int& DstNId) const { int EId; return IsEdge(SrcNId, DstNId, EId)?EId:-1; }
  /// Returns an iterator referring to the first edge in the graph.
  //TEdgeI BegEI() const { return TEdgeI(EdgeH.BegI(), this); }
  /// Returns an iterator referring to the past-the-end edge in the graph.
  //TEdgeI EndEI() const { return TEdgeI(EdgeH.EndI(), this); }
  /// Returns an iterator referring to edge with edge ID EId.
  //TEdgeI GetEI(const int& EId) const { return TEdgeI(EdgeH.GetI(EId), this); }
  /// Returns an iterator referring to edge (SrcNId, DstNId) in the graph.
  //TEdgeI GetEI(const int& SrcNId, const int& DstNId) const { return GetEI(GetEId(SrcNId, DstNId)); }

  /// Gets a vector IDs of all edges in the graph.
  //void GetEIdV(TIntV& EIdV) const;

  /// Deletes all nodes and edges from the graph.
  void Clr() { TNEANet::Clr(); TypeEdgeH.Clr(); OutEdgeV.Clr(); InEdgeV.Clr(); MxTypeEId = 0; NTypeId = -1;}


  /// Attribute based add function for attr to Int value. ##TNEANet::AddIntAttrDatN
  //int AddIntAttrDatN(const TNodeI& NodeI, const TInt& value, const TStr& attr) { return AddIntAttrDatN(NodeI.GetId(), value, attr); }
  //int AddIntAttrDatN(const int& NId, const TInt& value, const TStr& attr);

  /// Gets the value of int attr from the node attr value vector.
  //TInt GetIntAttrDatN(const TNodeI& NodeI, const TStr& attr) { return GetIntAttrDatN(NodeI.GetId(), attr); }
  //TInt GetIntAttrDatN(const int& NId, const TStr& attr);

  /// Gets the index of the node attr value vector specified by \c attr (same as GetAttrIndN for compatibility reasons).
  int GetIntAttrIndN(const TStr& attr);
  /// Gets the index of the node attr value vector specified by \c attr.
  int GetAttrIndN(const TStr& attr);

  /// Gets the value of an int node attr specified by node iterator \c NodeI and the attr \c index.
  TInt GetIntAttrIndDatN(const TNodeI& NodeI, const int& index) { return GetIntAttrIndDatN(NodeI.GetId(), index); }
  /// Gets the value of an int node attr specified by node ID \c NId and the attr \c index.
  TInt GetIntAttrIndDatN(const int& NId, const int& index);

  /// Gets the value of a string node attr specified by node iterator \c NodeI and the attr \c index.
  TStr GetStrAttrIndDatN(const TNodeI& NodeI, const int& index) { return GetStrAttrIndDatN(NodeI.GetId(), index); }
  /// Gets the value of a string node attr specified by node ID \c NId and the attr \c index.
  TStr GetStrAttrIndDatN(const int& NId, const int& index);

  /// Gets the value of a float node attr specified by node iterator \c NodeI and the attr \c index.
  TFlt GetFltAttrIndDatN(const TNodeI& NodeI, const int& index) { return GetFltAttrIndDatN(NodeI.GetId(), index); }
  /// Gets the value of a float node attr specified by node ID \c NId and the attr \c index.
  TFlt GetFltAttrIndDatN(const int& NId, const int& index);

  /// Gets the value of int attr from the edge attr value vector.
  TInt GetIntAttrDatE(const TEdgeI& EdgeI, const TStr& attr) { return GetIntAttrDatE(EdgeI.GetId(), attr); }
  TInt GetIntAttrDatE(const int& EId, const TStr& attr);
  /// Gets the value of str attr from the edge attr value vector.
  TStr GetStrAttrDatE(const TEdgeI& EdgeI, const TStr& attr) { return GetStrAttrDatE(EdgeI.GetId(), attr); }
  TStr GetStrAttrDatE(const int& EId, const TStr& attr);
  /// Gets the value of flt attr from the edge attr value vector.
  TFlt GetFltAttrDatE(const TEdgeI& EdgeI, const TStr& attr) { return GetFltAttrDatE(EdgeI.GetId(), attr); }
  TFlt GetFltAttrDatE(const int& EId, const TStr& attr);

  /// Gets the index of the edge attr value vector specified by \c attr (same as GetAttrIndE for compatibility reasons).
  int GetIntAttrIndE(const TStr& attr);
  /// Gets the index of the edge attr value vector specified by \c attr.
  int GetAttrIndE(const TStr& attr);

  /// Gets the value of an int edge attr specified by edge iterator \c EdgeI and the attr \c index.
  TInt GetIntAttrIndDatE(const TEdgeI& EdgeI, const int& index) { return GetIntAttrIndDatE(EdgeI.GetId(), index); }
  /// Gets the value of an int edge attr specified by edge ID \c EId and the attr \c index.
  TInt GetIntAttrIndDatE(const int& EId, const int& index);
 
  /// Gets the value of a float edge attr specified by edge iterator \c EdgeI and the attr \c index.
  TFlt GetFltAttrIndDatE(const TEdgeI& EdgeI, const int& index) { return GetFltAttrIndDatE(EdgeI.GetId(), index); }
  /// Gets the value of an int edge attr specified by edge ID \c EId and the attr \c index.
  TFlt GetFltAttrIndDatE(const int& EId, const int& index);
 
  /// Gets the value of a string edge attr specified by edge iterator \c EdgeI and the attr \c index.
  TStr GetStrAttrIndDatE(const TEdgeI& EdgeI, const int& index) { return GetStrAttrIndDatE(EdgeI.GetId(), index); }
  /// Gets the value of an int edge attr specified by edge ID \c EId and the attr \c index.
  TStr GetStrAttrIndDatE(const int& EId, const int& index);
 
  /// Deletes the node attribute for NodeI.
  int DelAttrDatN(const TNodeI& NodeI, const TStr& attr) { return DelAttrDatN(NodeI.GetId(), attr); } 
  int DelAttrDatN(const int& NId, const TStr& attr); 
  /// Deletes the edge attribute for NodeI.
  int DelAttrDatE(const TEdgeI& EdgeI, const TStr& attr) { return DelAttrDatE(EdgeI.GetId(), attr); } 
  int DelAttrDatE(const int& EId, const TStr& attr); 

  /// Adds a new Int node attribute to the hashmap.
  int AddIntAttrN(const TStr& attr, TInt defaultValue=TInt::Mn);
  /// Adds a new Str node attribute to the hashmap.
  int AddStrAttrN(const TStr& attr, TStr defaultValue=TStr::GetNullStr());
  /// Adds a new Flt node attribute to the hashmap.
  int AddFltAttrN(const TStr& attr, TFlt defaultValue=TFlt::Mn);

  /// Adds a new Int edge attribute to the hashmap.
  int AddIntAttrE(const TStr& attr, TInt defaultValue=TInt::Mn);
  /// Adds a new Str edge attribute to the hashmap.
  int AddStrAttrE(const TStr& attr, TStr defaultValue=TStr::GetNullStr());
  /// Adds a new Flt edge attribute to the hashmap.
  int AddFltAttrE(const TStr& attr, TFlt defaultValue=TFlt::Mn);

  /// Removes all the values for node attr.
  int DelAttrN(const TStr& attr);
  /// Removes all the values for edge  attr.
  int DelAttrE(const TStr& attr);

  // Returns true if \c attr exists for node \c NId and has default value.
  bool IsAttrDeletedN(const int& NId, const TStr& attr) const;
  // Returns true if Int \c attr exists for node \c NId and has default value.
  bool IsIntAttrDeletedN(const int& NId, const TStr& attr) const;
  // Returns true if Str \c attr exists for node \c NId and has default value.
  bool IsStrAttrDeletedN(const int& NId, const TStr& attr) const;
  // Returns true if Flt \c attr exists for node \c NId and has default value.
  bool IsFltAttrDeletedN(const int& NId, const TStr& attr) const;

  // Returns true if NId attr deleted for current node attr iterator.
  bool NodeAttrIsDeleted(const int& NId, const TStrIntPrH::TIter& NodeHI) const;
  // Returns true if NId attr deleted value for current node int attr iterator.
  bool NodeAttrIsIntDeleted(const int& NId, const TStrIntPrH::TIter& NodeHI) const;
  // Returns true if NId attr deleted value for current node str attr iterator.
  bool NodeAttrIsStrDeleted(const int& NId, const TStrIntPrH::TIter& NodeHI) const;
  // Returns true if NId attr deleted value for current node flt attr iterator.
  bool NodeAttrIsFltDeleted(const int& NId, const TStrIntPrH::TIter& NodeHI) const;

  // Returns true if \c attr exists for edge \c EId and has default value.
  bool IsAttrDeletedE(const int& EId, const TStr& attr) const;
  // Returns true if Int \c attr exists for edge \c EId and has default value.
  bool IsIntAttrDeletedE(const int& EId, const TStr& attr) const;
  // Returns true if Str \c attr exists for edge \c NId and has default value.
  bool IsStrAttrDeletedE(const int& EId, const TStr& attr) const;
  // Returns true if Flt \c attr exists for edge \c NId and has default value.
  bool IsFltAttrDeletedE(const int& EId, const TStr& attr) const;

  // Returns true if EId attr deleted for current edge attr iterator.
  bool EdgeAttrIsDeleted(const int& EId, const TStrIntPrH::TIter& EdgeHI) const;
  // Returns true if EId attr deleted for current edge int attr iterator.
  bool EdgeAttrIsIntDeleted(const int& EId, const TStrIntPrH::TIter& EdgeHI) const;
  // Returns true if EId attr deleted for current edge str attr iterator.
  bool EdgeAttrIsStrDeleted(const int& EId, const TStrIntPrH::TIter& EdgeHI) const;
  // Returns true if EId attr deleted for current edge flt attr iterator.
  bool EdgeAttrIsFltDeleted(const int& EId, const TStrIntPrH::TIter& EdgeHI) const;

  // Returns node attribute value, converted to Str type.
  TStr GetNodeAttrValue(const int& NId, const TStrIntPrH::TIter& NodeHI) const;
  // Returns edge attribute value, converted to Str type.
  TStr GetEdgeAttrValue(const int& EId, const TStrIntPrH::TIter& EdgeHI) const;

  // Get the sum of the weights of all the outgoing edges of the node.
  TFlt GetWeightOutEdges(const TNodeI& NI, const TStr& attr);
  // Check if there is an edge attribute with name attr.
  bool IsFltAttrE(const TStr& attr);
  // Check if there is an edge attribute with name attr.
  bool IsIntAttrE(const TStr& attr);
  // Check if there is an edge attribute with name attr.
  bool IsStrAttrE(const TStr& attr);
  // Get Vector for the Flt Attribute attr.
  TVec<TFlt>& GetFltAttrVecE(const TStr& attr);
  // Get keyid for edge with id EId.
  int GetFltKeyIdE(const int& EId);

  //Fills OutWeights with the outgoing weight from each node.
  void GetWeightOutEdgesV(TFltV& OutWeights, const TFltV& AttrVal) ;
  /// Fills each of the vectors with the names of node attributes of the given type.
  void GetAttrNNames(TStrV& IntAttrNames, TStrV& FltAttrNames, TStrV& StrAttrNames) const;
  /// Fills each of the vectors with the names of edge attributes of the given type.
  void GetAttrENames(TStrV& IntAttrNames, TStrV& FltAttrNames, TStrV& StrAttrNames) const;

  /// Returns a small multigraph on 5 nodes and 6 edges. ##TNEANet::GetSmallGraph
  static PNEANet GetSmallGraph();
  friend class TPt<TNEANetMM>;
};

// set flags
namespace TSnap {
template <> struct IsMultiGraph<TNEANetMM> { enum { Val = 1 }; };
template <> struct IsDirected<TNEANetMM> { enum { Val = 1 }; };
}
#endif // NETWORKMM_H
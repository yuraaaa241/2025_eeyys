/**     @file ModelPart.h
  *
  *     EEEE2076 - Software Engineering & VR Project
  *
  *     Template for model parts that will be added as treeview items
  *
  *     P Evans 2022
  */

#ifndef VIEWER_MODELPART_H
#define VIEWER_MODELPART_H

#include <QString>
#include <QList>
#include <QVariant>

  // VTK headers - commented out for now
  // #include <vtkSmartPointer.h>
  // #include <vtkMapper.h>
  // #include <vtkActor.h>
  // #include <vtkSTLReader.h>
  // #include <vtkColor.h>

class ModelPart {
public:
    ModelPart(const QList<QVariant>& data, ModelPart* parent = nullptr);
    ~ModelPart();

    void appendChild(ModelPart* item);
    ModelPart* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;

    void set(int column, const QVariant& value);

    ModelPart* parentItem();
    int row() const;

    void setColour(const unsigned char R, const unsigned char G, const unsigned char B);
    unsigned char getColourR();
    unsigned char getColourG();
    unsigned char getColourB();

    void setVisible(bool isVisible);
    bool visible();

    void loadSTL(QString fileName);

private:
    QList<ModelPart*>   m_childItems;
    QList<QVariant>     m_itemData;
    ModelPart* m_parentItem;

    bool                isVisible;

    unsigned char       colourR;
    unsigned char       colourG;
    unsigned char       colourB;
};

#endif
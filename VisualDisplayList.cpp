
#include <windows.h>
#include <gl/gl.h>
#include "VisualDisplayList.h"
#include "Object.h"
#include "Presentation.h"
#include "Logger.h"

namespace tlib
{

    OCVisualDisplayList::~OCVisualDisplayList() {
        glDeleteLists( m_uiListId, 1 );
    }

    void OCVisualDisplayList::render() const
    {
        // get the object's position
        const Vector3f& pos = getOwner()->getPos();

        // apply color/material/texture
        IComponent *comp = m_oOwner->getComponent("presentation");
        IOCPresentation *pres = static_cast<IOCPresentation*>(comp);
        if( pres )
            pres->apply();

        glPushMatrix();
            glTranslatef( pos.x(), pos.y(), pos.z() );
            
            // Load transformation quaternion and apply rotations
            getOwner()->getDir().toMatrix(m_fRotMatrix);
            glMultMatrixf(m_fRotMatrix);

            glCallList( m_uiListId );
        glPopMatrix();
    }

    void OCVisualDisplayList::generate()
    {
        _LOG("Generating display list...");
        m_uiListId = glGenLists(1);
        if( !glIsList(m_uiListId) ) {
            _LOG("Failed to generate display list(" 
                 +toStr<int>(m_uiListId)+ ")");
        } else {
            _LOG("Generated display list(" 
                 +toStr<int>(m_uiListId)+ ")");

            // Build display list
            glNewList( m_uiListId, GL_COMPILE );
                buildObject();
            glEndList();
        }

    } // end generate()

} // end of namespace tlib
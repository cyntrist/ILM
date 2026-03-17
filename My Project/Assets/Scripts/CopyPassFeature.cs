using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;
using UnityEngine.Rendering.Universal;

public class CopyPassFeature : ScriptableRendererFeature
{
    private CopyPass m_CopyPass;

    [SerializeField]
    private RenderPassEvent _renderPassEvent;

    // se llama a esto cada vez que se cambia algo (incluyendo en su creación)
    public override void Create()
    {
        m_CopyPass = new CopyPass();
        m_CopyPass.renderPassEvent = _renderPassEvent;
    } 

    // se llama una vez por frame
    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        renderer.EnqueuePass(m_CopyPass);

        // en el frame debugger aparece la etapa copy pass
    }
}
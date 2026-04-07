using System;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;
using UnityEngine.Rendering.RenderGraphModule;

public class ToonShadingFeature : ScriptableRendererFeature
{
    [SerializeField] private Material _toonMaterial;
    [SerializeField] [Range(0, 10)] private int factor = 7;
    private ToonShadingPass m_ToonShadingPass;

    public override void Create()
    {
        m_ToonShadingPass = new ToonShadingPass();
        m_ToonShadingPass.renderPassEvent = RenderPassEvent.AfterRenderingPostProcessing;
    }

    protected override void Dispose(bool disposing)
    {
        base.Dispose(disposing);
        CoreUtils.Destroy(_toonMaterial);
    }

    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        if (factor == 0) return;

        Shader s = Shader.Find("Hidden/Toon");

        if (s != null)
        {
            _toonMaterial = CoreUtils.CreateEngineMaterial(s);

            if (_toonMaterial == null)
            {
                return;
            }

            m_ToonShadingPass.Setup(factor, _toonMaterial);
        }
    }
}
